-- Create database
CREATE DATABASE my_database;

-- Use database
USE my_database;

-- Create table Employees
CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Department VARCHAR(50),
    Salary INT
);

-- Insert data into Employees table
INSERT INTO Employees (EmployeeID, FirstName, LastName, Department, Salary)
VALUES (1, 'John', 'Smith', 'HR', 50000),
       (2, 'Jane', 'Doe', 'IT', 60000),
       (3, 'David', 'Johnson', 'Finance', 70000),
       (4, 'Emily', 'Jones', 'Marketing', 55000),
       (5, 'Michael', 'Brown', 'Sales', 80000);

-- Create table Customers
CREATE TABLE Customers (
    CustomerID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Address VARCHAR(100),
    City VARCHAR(50)
);

-- Insert data into Customers table
INSERT INTO Customers (CustomerID, FirstName, LastName, Address, City)
VALUES (1, 'Adam', 'Lee', '123 Main St.', 'New York'),
       (2, 'Sarah', 'Kim', '456 Oak St.', 'Chicago'),
       (3, 'Chris', 'Chen', '789 Pine St.', 'San Francisco'),
       (4, 'Elizabeth', 'Wang', '1010 Maple St.', 'Los Angeles'),
       (5, 'Alex', 'Wu', '1212 Cedar St.', 'Miami');

-- Create table Orders
CREATE TABLE Orders (
    OrderID INT PRIMARY KEY,
    CustomerID INT,
    EmployeeID INT,
    OrderDate DATE,
    TotalAmount INT,
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    FOREIGN KEY (EmployeeID) REFERENCES Employees(EmployeeID)
);

-- Insert data into Orders table
INSERT INTO Orders (OrderID, CustomerID, EmployeeID, OrderDate, TotalAmount)
VALUES (1, 1, 2, '2022-01-01', 100),
       (2, 2, 3, '2022-02-02', 200),
       (3, 3, 4, '2022-03-03', 300),
       (4, 4, 5, '2022-04-04', 400),
       (5, 5, 1, '2022-05-05', 500);

-- Create table Products
CREATE TABLE Products (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(50),
    Category VARCHAR(50),
    Price INT
);

-- Insert data into Products table
INSERT INTO Products (ProductID, ProductName, Category, Price)
VALUES (1, 'iPhone 13', 'Electronics', 1200),
       (2, 'Macbook Air', 'Electronics', 1000),
       (3, 'Nike Air Max', 'Shoes', 120),
       (4, 'Levi\'s Jeans', 'Clothing', 80),
       (5, 'Canon EOS R6', 'Cameras', 2000);

-- Create table Suppliers
CREATE TABLE Suppliers (
    SupplierID INT PRIMARY KEY,
    SupplierName VARCHAR(50),
    Address VARCHAR(100),
    City VARCHAR(50)
);

-- Insert data into Suppliers table
INSERT INTO Suppliers (SupplierID, SupplierName, Address, City)
VALUES (1, 'ABC Company', '123 Main St.', 'New York'),
       (2, 'XYZ Corporation

