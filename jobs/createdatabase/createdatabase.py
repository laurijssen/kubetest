import pyodbc
import os

server = '192.168.56.3,31433' 
database = 'geocachefriends' 
username = 'sa' 
password = os.getenv('SA_PASSWORD')

cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';UID='+username+';PWD='+ password)
cursor = cnxn.cursor()

cursor.execute("SELECT @@version;") 
row = cursor.fetchone() 
while row: 
    print(row[0])
    row = cursor.fetchone()