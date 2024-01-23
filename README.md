# Restaurant Management System - C Programming

This program manages a restaurant system with products, orders, and tables. It reads instructions from the "Instructions.txt" file to perform various functions such as creating a list of products, adding items to the kitchen, taking orders, canceling orders, and removing tables.

## Functions

1. **Create Kitchen**
   - Read product information from "Manot.txt" and create a list of products.

2. **Add Items to Kitchen**
   - Add a specified quantity of a product to the kitchen.

3. **Order Item**
   - Place an order for a specified quantity of a product at a specific table.

4. **Cancel Order**
   - Cancel a previous order for a specified quantity of a product at a specific table.

5. **Remove Table**
   - Remove a table if it has no pending orders.

## Input Files

1. **Manot.txt**
   - Contains information about various products in the kitchen.

2. **Instructions.txt**
   - Contains a sequence of instructions to perform various functions.

## Example Usage
**"Instructions.txt" content:**
- 1
- 2 Bread 10
- 1 Milk 2
- 2 Cheese 3
- 3

  
**Result:**
- The kitchen was created
- 10 Bread were added to the kitchen
- 2 Milk were ordered for table 1
- 3 Cheese order canceled for table 2
- The table number 3 is not ordered yet


