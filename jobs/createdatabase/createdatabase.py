import pyodbc
import os

server = '192.168.56.3,31433'
database = 'geocachefriends'
username = 'sa'
password = os.getenv('SA_PASSWORD')

cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER=' +
                      server+';DATABASE='+database+';UID='+username+';PWD=' + password)
cursor = cnxn.cursor()


def execute(q):
    try:
        cursor.execute(qry)
        cnxn.commit()
        print(qry + ' completed')
    except:
        print('exception on execute query')


for qry in ["""if not exists (select 1 from information_schema.tables where table_name = 'users')
           create table users (id int not null primary key, firstname nvarchar(128), lastname nvarchar(128), loginname nvarchar(32), password nvarchar(32))""",
            """insert into users values (1, 'serve', 'laurijssen', 'lau', 'test')""",
            """if not exists (select 1 from information_schema.tables where table_name = 'locations')
            create table locations (id int identity(1, 1) primary key, userid int foreign key references users, lon FLOAT, lat FLOAT)"""
            ]:
    print(qry)
    execute(qry)
