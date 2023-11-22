"""
\\ Database, Relation Name and Relation Schema \\
database = NewDB
relation = EmpDetails
Schema:

CREATE TABLE EmpDetails(
	empID int,
	empName varchar(50),
	empSalary double,
	PRIMARY KEY(empID)
);
"""

import mysql.connector
from mysql.connector import Error

connection = mysql.connector.connect(host='localhost',
									 database='nameofdatabase',
									 user='yourusername',
									 password='yourpassword')  # insert your system details here

dbInfo = connection.get_server_info()
print("Connected to MySQL Server:", dbInfo)
mycursor = connection.cursor()

ch = 0
while ch != 5:
	print("\n(1) Insert Record\n(2) Update Record\n(3) Delete Record\n(4) Display All Records\n(5) Exit\n")
	ch = int(input(">> "))

	if ch == 1:
		print("\t=-=-= Data Insert =-=-=\n")
		n = int(input("How many records do you want to insert?\n>> "))
		for i in range(0, n):
			inputID = int(input("Enter Employee ID: "))
			inputName = input("Enter Employee Name: ")
			inputSalary = float(input("Enter Employee Salary: "))

			sql = f"INSERT INTO employee VALUES ({inputID}, '{inputName}', {inputSalary})"
			mycursor.execute(sql)
			connection.commit()
		print("\nRecord Inserted Successfully!") if n == 1 else print("\nRecords Inserted Successfully!")
	
	elif ch == 2:
		print("\t=-=-= Data Update =-=-=\n")
		print("(1) Update Employee Name\n(2) Enter Employee Salary")
		opt = int(input(">> "))

		if opt == 1:
			inputID = int(input("Enter Employee ID: "))
			inputName = input("Set new name: ")
			sql = f"UPDATE employee SET Name = '{inputName}' WHERE EmpID = {inputID}"
			mycursor.execute(sql)

		elif opt == 2:
			inputID = int(input("Enter Employee ID: "))
			inputSalary = input("Set new salary: ")
			sql = f"UPDATE employee SET Salary = {inputSalary} WHERE EmpID = {inputID}"
			print("\nRecord Updated Successfully!")
			mycursor.execute(sql)
        
    connection.commit()
	
	elif ch == 3:
		print("\t=-=-= Data Delete =-=-=\n")
		inputID = int(input("Enter ID of employee record to delete: "))
		sql = f"DELETE FROM employee WHERE EmpID = {inputID}"
		mycursor.execute(sql)
		connection.commit()
		print("\nRecord Deleted Successfully!")
        connection.commit()
	
	elif ch == 4:
		mycursor.execute("SELECT * FROM employee")
		records = mycursor.fetchall()
		print("Employee ID\tEmployee Name\tSalary\n")
		for i in records:
			print(f"{i[0]}\t\t{i[1]}\t${i[2]}")
			# 'i' is an SQL record so it becomes a list containing all attributes
	
	else:
		print("\nExiting...")
		exit()


connection.close()
