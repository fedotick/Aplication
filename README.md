# Practice 2022 (CEITI)

Repositories with solved tasks.

## Condition

Information about products of some store (name, units, category code, quantity, production date, expiration date, price) is contained in the text file `Products.txt`. Each line of the test file corresponds to information about one product and vice versa.

Information about product categories (category code, name) is contained in the text file `Category.txt`. Each line of the test file corresponds to information about a single category and vice versa.

The price of a product varies depending on its expiration date as follows:
- If the expiration date has expired, the price of the item is 0
- If the expiration date is half over, the product is sold at a 20% discount.
- If the expiration date is a quarter away, the product is discounted 50%.

## Tasks

Create a console application that contains menus and functions that perform the following actions at the user's option:
1.	Display information about all products on the screen.
2.	Display information about all categories.
3.	Add information about a new product.
4.	Adding information about a new category.
5.	Deleting information about a product whose name is entered from the keyboard.
6.	Deleting information about a category, the name of which is entered from the keyboard.
7.	Editing information about the product, the name of which is entered from the keyboard.
8.	Editing information about the category, the name of which is entered from the keyboard.
9.	Creating a text file `Sale.txt`, containing information about goods with a new price calculated for the current date. (! The file contains the category name, not the code)
10.	Display an alphabetized list of products of a specified category.
11.	Displaying information about the most expensive and the cheapest goods for the current date.
12.	Displaying the total cost of all goods in the warehouse.
