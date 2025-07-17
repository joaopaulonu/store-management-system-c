# TechStore Sales System
TechStore Sales and Inventory Management System in C

The “TechStore Sales and Inventory Management System in C” is a software solution developed entirely in the C programming language. It was created collaboratively by João Paulo Nunes Andrade (myself), Gabriel Oliveira, and Caique Andraus. Our main goal with this system was to apply and consolidate our Computer Engineering knowledge in a practical way, by developing a tool that demonstrates how programming can positively impact process improvement. This passion for innovative and efficient solutions drives us on our academic and professional journey.

Implemented Features
The system operates through an interactive console menu and offers a set of essential functionalities for managing a sales and inventory environment:

Product Registration
The cadastrarProduto function allows adding new items to the store's inventory. The system performs input validation to ensure data integrity:

Checks if the product code is unique and positive

Ensures the name is not empty

Verifies the sale price is positive

Confirms the stock quantity is non-negative

Each product is stored in a struct Produto, which contains:

Product code

Name

Sale price

Stock quantity

Sales Recording
The registrarVenda function processes sales transactions. When a sale is recorded, the system asks for the product code and desired quantity. It verifies if the product exists and if there is sufficient stock. For valid sales:

The product stock is automatically updated

Sale details (sale ID, sold product, and total amount) are stored in a struct Venda

Detailed Listings
Available Products (listarProdutos): Displays all products with positive stock for quick reference.

Out-of-Stock Products (listarProdutosEmFalta): Lists products with zero stock, aiding restocking decisions.

Sales History (listarVendas): Shows a complete history of processed sales, including sale ID, product details, and revenue per transaction.

Management Reports
The reporting section (relatorios) provides valuable insights into TechStore’s performance:

Best-Selling Product (maisVendido): Identifies the product sold in the highest quantity.

Sales per Product (vendasPorProduto): Breaks down the number of sales and total quantity sold per product for performance analysis.

Total Revenue (somaDasVendas): Calculates the total revenue generated from all registered sales.

Code Structure and Applied Concepts
The system was developed following structured programming principles and modularity, ensuring readability and maintainability. Each functionality is encapsulated in specific functions (cadastrarProduto, registrarVenda, listarProdutos, etc.), distributing responsibilities clearly among the team.

Technically, the system makes extensive use of:

Structs: To define complex data types (Produto and Venda), grouping related data (e.g., code, name, price, stock).

Arrays: Used as the primary data structure (Produto produtos[MAX_PRODUTOS], Venda vendas[MAX_VENDAS]) to store collections of products and sales in memory. The constants MAX_PRODUTOS (50) and MAX_VENDAS (100) define maximum system capacity.

Pointers: Passing product and sales counts by reference (int *qtdProdutos, int *qtdVendas) so functions can modify global values.

Control Flow: if/else, for, and switch-case are used for business logic, validation, and menu navigation.

String Handling: Functions like fgets and strcspn ensure safe input reading, avoiding issues with spaces and line breaks.

Localization (setlocale): setlocale(LC_ALL, "Portuguese") ensures proper display of accented characters and numeric formatting in the console.

Screen Clearing (system("cls")): Used for a cleaner and more user-friendly console interface.

This project reflects our ability to turn requirements into functional code, applying knowledge in data structures, programming logic, and input handling.
