#!/usr/bin/python3
import sys
import os
import urllib
import urllib.request
import zipfile
import tarfile
import shutil
import distutils.dir_util
import subprocess

savedData={'version' : '0', 'modlist' : '', 'modserverurl' : 'https://ruler501git.tk/acr/mods'}

def sanitizePath(path):
	if sys.platform.startswith('win32'):
		return path.replace('/','\\')
	elif sys.platform.startswith('linux'):
		return path
	else:
		return path#random guess that I hope works in most cases.

def pruneMod(badMod):
	newList=''
	for mod in savedData['modlist'].split(', '):
		if mod.split('-')[0].strip() != badMod.strip():
			if newList != '':
				newList += ', '
			newList += mod
	savedData['modlist'] = newList

def loadData():
	try:
		dataConfig = open('updater.conf', 'r')
	except FileNotFoundError:
		init(' ')
		return
	for line in dataConfig.readlines():
		line= line.strip()
		if line == '':
			continue
		try:
			savedData[line.split('=')[0]]=line.split('=')[1]
		except KeyError:
			print("Bad config file")
	dataConfig.close()

def writeClientExecutable():
	extraMods=''
	for mod in savedData['modlist'].split(','):
		extraMods+='--mod=mods/'+mod.strip().split('-')[0]+' '
	if sys.platform.startswith('win32'):
		with open('Client.bat', 'w') as batch:
			batch.write('cd acr\nbin_win32\\ac_client.exe --home=data '+extraMods+'--mod=acr --init %*')
	elif sys.platform.startswith('linux'):
		#ugly but works :P -- rXn
		with open('acr/client.sh', 'r') as origFile:
			with open('Client.sh', 'w') as shell:
				#first cd to acr
				origFileLine = origFile.readline()
				shell.write(origFileLine)
				shell.write('cd acr/\n')
				origFileLine = origFile.readline()
				while origFileLine.find('CUBE_OPTIONS') == -1:
					shell.write(origFileLine)
					origFileLine = origFile.readline()
				#now skip and replace the "bad" line:
				shell.write('CUBE_OPTIONS="--home=data '+extraMods+'--mod=acr --init"\n')
				origFileLine = origFile.readline()
				origFileLine = origFile.readline()
				#and write the remaining stuff
				shell.write(origFile.read())
				#shell.write('/bin/sh\ncd acr\nCUBE_DIR=$(dirname "$(readlink -f .)/acr")\nCUBE_OPTIONS="--home=data '+extraMods+'--mod=acr --init"\ncd "${CUBE_DIR}"\nexec "${CUBE_DIR}/bin_linux/linux_client" ${CUBE_OPTIONS} "$@"')
	else:
		print("You have to supply your own bat/sh type file. I don't know how to write one for your system")
		return
	print("Wrote Client Launcher")

def writeServerExecutable():
	extraMods=''
	for mod in savedData['modlist'].split(','):
		extraMods+='--mod='+mod.split('-')[0]+' '
	if sys.platform.startswith('win32'):
		with open('Server.bat', 'w') as batch:
			batch.write('cd acr\nbin_win32\\ac_server.exe --mod=acr '+extraMods+'-Cconfig/servercmdline.txt %*\npause')
	elif sys.platform.startswith('linux'):
		with open('Server.sh', 'w') as shell:
			shell.write('#!/bin/sh\ncd acr\nCUBE_DIR=$(dirname "$(readlink -f $0)")\nCUBE_OPTIONS="--mod=acr '+extraMods+'"\nCUBE_OPTIONFILE=-Cconfig/servercmdline.txt\ncd "${CUBE_DIR}"\nexec "${CUBE_DIR}/bin_linux/linux_server" ${CUBE_OPTIONS} ${CUBE_OPTIONFILE} "$@"')
	else:
		print("You have to supply your own bat/sh type file. I don't know how to write one for your system")
		return
	print("Wrote Server Launcher")

def init(arguments):
	print("Initiating")
	with open('updater.conf', 'w') as data:
		data.write('version='+savedData['version']+'\nmodlist='+savedData['modlist']+'\nmodserverurl='+savedData['modserverurl'])
	print("Config successfuly written")

def updateAll(arguments):
	print("Updating Everything")
	updateMe(arguments)
	updateACR(arguments)
	updateMods(arguments)
	print("Done Updating")

def updateMe(arguments):
	print("Checking for updates to me")
	print("I no know how to update me")
	#implement later

def updateACR(arguments):
	print("Checking for updates to ACR")
	downloadPage = urllib.request.urlopen("https://code.google.com/p/assaultcuber/downloads/list")
	data = str(downloadPage.read(), encoding='utf8')
	#print(data)
	version = data.split(' - Source Code')[0].split(' ')[-1]
	#print(version)
	if version == savedData['version']:
		print("No update available")
	else:
		update = input("Do you want to update to "+version+"? (y/n)")
		if update == 'n' or update == 'N':
			print("ACR not updated")
			return
		elif update == 'y' or update == 'Y':
			print("Downloading ACR "+version)
			if sys.platform.startswith('win32'):
				downloadURL = 'https:'+data[:data.find('-w.zip"')+6].split('"')[-1]
				#print(downloadURL)
				req = urllib.request.Request(downloadURL)
				response = urllib.request.urlopen(req)
				shutil.copyfileobj(response, open(os.path.join(os.getcwd(),'acr.zip'), 'wb'))
				print('Extracting ACR')
				with zipfile.ZipFile(os.path.join(os.getcwd(),'acr.zip')) as temp:
					temp.extractall(os.path.join(os.getcwd(),'tmp'))
				os.remove(os.path.join(os.getcwd(),'acr.zip'))
				#print(savedData['version'])
				if savedData['version'] == '0':
					print('Moving Files')
					os.rename('tmp','acr')
				else:
					print('Backing up Files')
					distutils.dir_util.mkpath(os.path.join(os.getcwd(),'backup'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr\\config'), os.path.join(os.getcwd(),'backup\\config'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr\\data'), os.path.join(os.getcwd(),'backup\\data'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr\\mods'), os.path.join(os.getcwd(),'backup\\mods'))
					shutil.rmtree(os.path.join(os.getcwd(), 'acr'))
					print('Moving Files')
					os.rename('tmp','acr')
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup\\config'), os.path.join(os.getcwd(),'acr\\config'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup\\data'), os.path.join(os.getcwd(),'acr\\data'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup\\mods'), os.path.join(os.getcwd(),'acr\\mods'))
					shutil.rmtree(os.path.join(os.getcwd(), 'backup'))
			elif sys.platform.startswith('linux'):
				downloadURL = 'https:'+data[:data.find('.tar.gz"')+7].split('"')[-1]
				#print(downloadURL)
				req = urllib.request.Request(downloadURL)
				response = urllib.request.urlopen(req)
				shutil.copyfileobj(response, open(os.path.join(os.getcwd(),'acr.tar.gz'), 'wb'))
				print('Extracting ACR')
				with tarfile.open(os.path.join(os.getcwd(),'acr.tar.gz'),'r') as temp:
	def is_within_directory(directory, target):
		
		abs_directory = os.path.abspath(directory)
		abs_target = os.path.abspath(target)
	
		prefix = os.path.commonprefix([abs_directory, abs_target])
		
		return prefix == abs_directory
	
	def safe_extract(tar, path=".", members=None, *, numeric_owner=False):
	
		for member in tar.getmembers():
			member_path = os.path.join(path, member.name)
			if not is_within_directory(path, member_path):
				raise Exception("Attempted Path Traversal in Tar File")
	
		tar.extractall(path, members, numeric_owner=numeric_owner) 
		
	
	safe_extract(temp, os.path.join(os.getcwd(),"tmp"))
				os.remove(os.path.join(os.getcwd(),'acr.tar.gz'))
				if savedData['version'] == '0':
					print('Moving Files')
					os.rename('tmp','acr')
				else:
					print('Backing up Files')
					distutils.dir_util.mkpath(os.path.join(os.getcwd(),'backup'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr/config'), os.path.join(os.getcwd(),'backup/config'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr/data'), os.path.join(os.getcwd(),'backup/data'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'acr/mods'), os.path.join(os.getcwd(),'backup/mods'))
					shutil.rmtree(os.path.join(os.getcwd(), 'acr'))
					print('Moving Files')
					os.rename('tmp','acr')
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup/config'), os.path.join(os.getcwd(),'acr/config'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup/data'), os.path.join(os.getcwd(),'acr/data'))
					distutils.dir_util.copy_tree(os.path.join(os.getcwd(),'backup/mods'), os.path.join(os.getcwd(),'acr/mods'))
					shutil.rmtree(os.path.join(os.getcwd(), 'backup'))
			else:
				print("Unsupported platform\nACR not updated")
				return
			savedData['version'] = version
			init(' ')
			writeClientExecutable()
			writeServerExecutable()
			print('Succesfully updated ACR')
	return

def updateMods(arguments):
	print("Mods not implemented yet")
	#print("Checking for updates to your mods")
	#implement later

def installMods(arguments):
	if len(arguments) < 3:
		print("You supplied no mods to install")
		return
	for mod in arguments[2:]:
		if mod.find('-') != -1:
			req = urllib.request.Request(savedData['modserverurl']+'/oldversions/'+mod+'.zip')
			response = urllib.request.urlopen(req)
			shutil.copyfileobj(response, open(os.path.join(os.getcwd(), mod+'.zip'), 'wb'))
			print('Extracting '+mod.split('-')[0])
			with zipfile.ZipFile(os.path.join(os.getcwd(), mod+'.zip')) as temp:
				temp.extractall(os.path.join(os.getcwd(), mod.split('-')[0]))
		else:
			print('Downloading '+mod)
			req = urllib.request.Request(savedData['modserverurl']+'/current/'+mod+'.zip')
			response = urllib.request.urlopen(req)
			shutil.copyfileobj(response, open(os.path.join(os.getcwd(),'acr.zip'), 'wb'))
			print('Extracting '+mod)
			with zipfile.ZipFile(os.path.join(os.getcwd(),'acr.zip')) as temp:
				temp.extractall(os.path.join(os.getcwd(), mod))
		if os.path.isdir(os.path.join(os.getcwd(),'acr/mods/'+mod.split('-')[0])):
			cont = input("Do you want to overwrite the old install? (y/n)")
			if cont == 'n' or cont == 'N':
				print(mod+' was not installed')
				return
			elif cont == 'y' or cont == 'Y':
				shutil.rmtree(os.path.join(os.getcwd(), 'acr/mods/'+mod.split('-')[0]))
				pruneMod(mod.split('-')[0])
			else:
				print('Unrecognized command. Exiting')
				return
		shutil.move(os.path.join(os.getcwd(), mod), os.path.join(os.getcwd(),'acr/mods/'+mod.split('-')[0]))
		if savedData['modlist'] != '':
			savedData['modlist'] += ', '
		savedData['modlist'] += mod
		if mod.find('-') == -1:
			savedData['modlist'] += '-0'
		print('Succesfully installed '+mod)
	init(' ')
	writeClientExecutable()
	writeServerExecutable()

def listMods(arguments):
	modList = urllib.request.urlopen(savedData['modserverurl']+'/list.py')
	data = str(modList.read(), encoding='utf8').strip()
	for line in data.split('\n'):
		if line.strip() != '':
			print(line.strip().split('-')[0])

def installLocalMod(arguments):
	if len(arguments) < 3:
		showHelp('updater.py','help','installlocalmod')
		return
	if arguments[2][-4:] != '.zip':
		print('File needs to be a zip')
		return
	name = arguments[2].split('-')[0]
	version = arguments[2].split('-')[1][:-4]
	if version == '':
		version = '0'
	if os.path.isdir(os.path.join(os.getcwd(),sanitizePath('acr/mods/'+name))):
		cont = input("Are you sure you want to overwrite "+name+"? (y/n)")
		if cont.lower() == 'n':
			print(name+' was not installed')
			return
		elif cont.lower() == 'y':
			print('Removing old install')
			shutil.rmtree(os.path.join(os.getcwd(), 'acr/mods/'+name))
		else:
			print('Unrecognized command. Exiting')
			return
	print("Extracting "+name)
	with zipfile.ZipFile(os.path.join(os.getcwd(),arguments[2])) as mod:
		mod.extractall(os.path.join(os.getcwd(),sanitizePath('acr/mods/'+name)))
	pruneMod(name)
	if savedData['modlist'] != '':
		savedData['modlist'] += ', '
	savedData['modlist'] += name+'-'+version
	init(' ')
	writeClientExecutable()
	writeServerExecutable()
	print(name+" finished being installed")

def removeMods(arguments):
	if len(arguments) < 3:
		showHelp('updater.py','help','removemods')
		return
	for mod in arguments[2:]:
		cont = input("Are you sure you want to remove "+mod+"? (y/n)")
		if cont.lower() == 'n':
			print(mod+' was not removed')
			return
		elif cont.lower() == 'y':
			print("Removing "+mod)
			shutil.rmtree(os.path.join(os.getcwd(),sanitizePath('acr/mods/'+mod)))
			pruneMod(mod)
			init(' ')
			writeClientExecutable()
			writeServerExecutable()
			print("Done removing "+mod)
		else:
			print("Unrecognised command. Exiting")
			return

def installedMods(arguments):
	for mod in savedData['modlist'].split(', '):
		print(mod.split('-')[0]+' version '+mod.split('-')[1])

def runClient(arguments):
	writeClientExecutable()
	if sys.platform.startswith('win32'):
		subprocess.call('Client.bat', shell=True)
	elif sys.platform.startswith('linux'):
		subprocess.call('Client.sh', shell=True)
	else:
		print("I don't recognize your OS")

def runServer(arguments):
	writeServerExecutable()
	if sys.platform.startswith('win32'):
		subprocess.call('Server.bat', shell=True)
	elif sys.platform.startswith('linux'):
		subprocess.call('Server.sh', shell=True)
	else:
		print("I don't recognize your OS")

def showHelp(*arguments):
	if len(arguments) > 2:
		print("Eek no implementations")
	else:
		print("You need to specify a valid option for the updater")
		print("Available options are:")
		print("init - Initiates the updater configs")
		print("updateall - Checks everything for updates")
		print("updateme - update the updater")
		print("updateacr - Checks for updates to ACR")
		print("updatemods - Check for mod updates")
		print("installmods <mod1>, <mod2>... - Comma separated list of mods to install")
		print("listmods - Gets the mod list from the server with versions")
		print("installlocalmod <file> - installs a zipfile as a mod")
		print("removemods <mod1>, <mod2>... - Comma separated list of mods to remove")
		print("installedmods - Prints out the installed mods along with versions")
		print("runclient - runs the client")
		print("runserver - runs the server")
		print("help <option> - Explains how to use <option> or if excluded gives you this dialogue")

runOption = {'init' : init, 'updateall' : updateAll, 'updateme' : updateMe, 'updateacr' : updateACR, 'updatemods' : updateMods, 'installmods' : installMods, 'listmods' : listMods, 'installlocalmod' : installLocalMod, 'removemods' : removeMods, 'installedmods' : installedMods, 'runclient' : runClient, 'runserver' : runServer, 'help' : showHelp}

def main():
	arguments = sys.argv
	if len(arguments) < 2:
		showHelp('')
	else:
		if arguments[1] != 'init':
			loadData()
		try:
			runOption[sys.argv[1]](sys.argv)
		except KeyError:
			showHelp('')

if __name__ == "__main__":
	main()
