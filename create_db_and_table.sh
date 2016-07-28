#!/bin/bash

echo "---"
echo "Create and Drop table products"
echo "---"



echo "Drop database test"
psql -U postgres -d template1 -c "DROP DATABASE test;"

echo "Create database test"
psql -U postgres -d template1 -c "CREATE DATABASE test;"

echo "Drop user"
psql -U postgres -d test -c "DROP USER test_user;"

echo "Create user and password"
psql -U postgres -d test -c "CREATE USER test_user WITH PASSWORD '12345';"

echo "Create privileges"
psql -U postgres -d test -c "GRANT ALL privileges ON DATABASE test TO test_user;"

echo "Create TABLE products"
psql -U postgres -d test -c "CREATE TABLE products (
	id PRIMARY KEY NOT NULL,
	title text,
	company_id integer NOT NULL,
	details text
	);"

psql -U postgres -d test -c "INSERT INTO  products(title, company_id, details) VALUES('Milk', '1', 'Milk fresh');"

psql -U postgres -d test -c "INSERT INTO  products(title, company_id, details) VALUES('Meat', '2', 'Meat without blood');"


