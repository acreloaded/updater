import sys
import urllib.request

SavedData={'version' : '2.5.9', }

def loadData():
	dataConfig = open('updater.conf', 'r')
	dataConfig.close()

def init(arguments):
	print("Initiating")
	#implement later

def updateAll(arguments):
	print("Updating Everything")
	updateMe(arguments)
	updateACR(arguments)
	updateMods(arguments)
	print("Done Updating")
	return

def updateMe(arguments):
	print("Checking for updates to me")
	#implement later

def updateACR(arguments):
	print("Checking for updates to ACR")
	
	downloadPage = urllib.request.urlopen("http://assaultcubes.codeplex.com/releases")
	data = str(downloadPage.read(), encoding='utf8')
	version = data.split('<title>')[1].split('</title>')[0].split('; ')[1]
	
	if version == SavedData['version']:
		print("No update available")
	else:
		update = input("Do you want to update to "+version+"? (y/n)")
		if update == 'n' or update == 'N':
			print("ACR not updated")
			return
		elif update == 'y' or update == 'Y':
			print("Updating to "+version)
			#implement later

def updateMods(arguments):
	print("Checking for updates to your mods")
	#implement later

def installMods(arguments):
	pass
	#implement later

def listMods(arguments):
	pass
	#implement later

def help(arguments):
	if arguments != None:
		print("EEk no implementations")
		return
	else:
		print("You need to specify an option for the updater")
		print("Available options are:")
		print("init - Initiates the updater configs")
		print("updateall - Checks everything for updates")
		print("updateme - update the updater")
		print("updateacr - Checks for updates to ACR")
		print("updatemods - Check for mod updates")
		print("installmods <name>,<mod2>... - Comma seperated list of mods to install")
		print("listmods - Gets the mod list from the server with versions")
		print("help <option> - Explains how to use <option> or if excluded gives you this dialog")
		return

runOption = {'init' : init, 'updateall' : updateAll, 'updateme' : updateMe, 'updateacr' : updateACR, 'updatemods' : updateMods, 'installmods' : installMods, 'listmods' : listMods, 'help' : help}

def main():
	arguments = sys.argv
	if len(arguments) < 2:
		help(None)
	else:
		loadData()
		runOption[sys.argv[1]](sys.argv)
	
if __name__ == "__main__":
    main()