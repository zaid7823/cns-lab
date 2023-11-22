import pymongo
from pymongo import MongoClient

mongo_host = 'localhost'
mongo_port = 27017

try:
	client = MongoClient(host=mongo_host, port=mongo_port)
	print("\nConnected to MongoDB\n")
except pymongo.errors.ConnectionFailure:
	print("Could not connect to MongoDB\n")

# Choosing a Database
print("Databases: ", client.list_database_names())
dbName = input("Enter DB Name: ")
db = client[f"{dbName}"]

# Choosing a collection under the Database
print("\nCollections: ", db.list_collection_names())
collName = input("Enter Collection Name: ")
collectionName = db[f"{collName}"]

# ===========================================
def insertDoc():
	insertDict = {}
	print("\n=-=-= Insert Document =-=-=\n")
	flag = "Y"
	while flag in ("y", "Y"):
		key = input("Enter an attribute: ")
		value = input("Enter value: ")
		insertDict[key] = int(value) if value.isdigit() else value
		flag = input("Enter more attributes? (Y/N): ")

	collectionName.insert_one(insertDict)
	print("\nDocument Inserted Successfully!\n")
# ===========================================
def updateDoc():
	print("\n=-=-= Update Document =-=-=\n")
	updateDict = {}
	newAtrributes = {}
	print("-- Set Filters --\n")
	flag = "Y"
	while flag in ("y", "Y"):
		key = input("Enter Attribute: ")
		value = input("Enter Value: ")
		updateDict[key] = int(value) if value.isdigit() else value
		flag = input("Set more filters? (Y/N): ")
	
	flag = "Y"
	print("\nSet New Attributes\n")
	while flag in ("Y", "y"):
		key = input("Enter Attribute:")
		value = input("Enter Value: ")

		newAtrributes[key] = int(value) if value.isdigit() else value
		flag = input("Change more attributes? (Y/N): ")
	
	collectionName.update_one(updateDict, {"$set": newAtrributes})
# ===========================================	
def deleteDoc():
	print("\n=-=-= Delete Document =-=-=\n")
	deleteDict = {}
	print("-- Set filters --\n")
	flag = "Y"
	while flag in ("y", "Y"):
		key = input("Enter Attribute: ")
		value = input("Enter Value: ")
		deleteDict[key] = int(value) if value.isdigit() else value
		flag = input("Set more filters? (Y/N): ")
	collectionName.delete_one(deleteDict)
# ===========================================
def displayAll():
	print("\n=-=-= Display Documents =-=-=\n")
	for i in collectionName.find():
		print(i)

# =-=-=-= Driver Code =-=-=-=
ch = 0
while ch != 5:
	print("(1) Insert Document\n(2) Update Document\n(3) Delete Document\n(4) Display All Records\n(5) Exit\n>> ", end="")
	ch = int(input())

	if ch == 1:
		insertDoc()
	
	elif ch == 2:
		updateDoc()

	elif ch == 3:
		deleteDoc()
	
	elif ch == 4:
		displayAll()
	
	elif ch == 5:
		print("\nExiting...\n")
		exit()
