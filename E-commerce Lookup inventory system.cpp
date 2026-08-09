#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// ================= PRODUCT CLASS =================

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int quantity;

    Product() {}

    Product(int id, string name, string category,
            double price, int quantity) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
    }

    void display() {
        cout << "\nProduct ID : " << id;
        cout << "\nName       : " << name;
        cout << "\nCategory   : " << category;
        cout << "\nPrice      : Rs. " << price;
        cout << "\nQuantity   : " << quantity;

        if (quantity == 0)
            cout << "\nStatus     : OUT OF STOCK";
        else if (quantity <= 5)
            cout << "\nStatus     : LOW STOCK";
        else
            cout << "\nStatus     : AVAILABLE";

        cout << "\n-----------------------------";
    }
};


// ================= BST NODE =================

class BSTNode {
public:
    Product product;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Product p) {
        product = p;
        left = NULL;
        right = NULL;
    }
};


// ================= INVENTORY SYSTEM =================

class InventorySystem {

private:

    // Hash Map for O(1) average product lookup
    unordered_map<int, Product> inventory;

    // Vector for storing products
    vector<Product> products;

    // Queue for restocking requests
    queue<int> restockQueue;

    // Stack for recent actions
    stack<string> actionHistory;

    // Root of BST
    BSTNode* root;


    // ================= BST INSERT =================

    BSTNode* insertBST(BSTNode* root, Product p) {

        if (root == NULL)
            return new BSTNode(p);

        if (p.id < root->product.id)
            root->left = insertBST(root->left, p);

        else if (p.id > root->product.id)
            root->right = insertBST(root->right, p);

        return root;
    }


    // ================= BST SEARCH =================

    BSTNode* searchBST(BSTNode* root, int id) {

        if (root == NULL || root->product.id == id)
            return root;

        if (id < root->product.id)
            return searchBST(root->left, id);

        return searchBST(root->right, id);
    }


    // ================= BST DISPLAY =================

    void inorder(BSTNode* root) {

        if (root == NULL)
            return;

        inorder(root->left);

        root->product.display();

        inorder(root->right);
    }


public:

    // ================= CONSTRUCTOR =================

    InventorySystem() {
        root = NULL;
    }


    // ================= ADD PRODUCT =================

    void addProduct() {

        int id;
        string name;
        string category;
        double price;
        int quantity;

        cout << "\nEnter Product ID: ";
        cin >> id;

        if (inventory.find(id) != inventory.end()) {
            cout << "\nProduct ID already exists!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Product Name: ";
        getline(cin, name);

        cout << "Enter Category: ";
        getline(cin, category);

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Quantity: ";
        cin >> quantity;

        Product p(id, name, category, price, quantity);

        // Add to hash map
        inventory[id] = p;

        // Add to vector
        products.push_back(p);

        // Add to BST
        root = insertBST(root, p);

        actionHistory.push("Added Product ID " + to_string(id));

        cout << "\nProduct added successfully!\n";
    }


    // ================= SEARCH PRODUCT =================

    void searchProduct() {

        int id;

        cout << "\nEnter Product ID to search: ";
        cin >> id;

        auto it = inventory.find(id);

        if (it == inventory.end()) {
            cout << "\nProduct not found!\n";
            return;
        }

        cout << "\nProduct Found:\n";
        it->second.display();

        actionHistory.push("Searched Product ID " + to_string(id));
    }


    // ================= UPDATE STOCK =================

    void updateStock() {

        int id;
        int quantity;

        cout << "\nEnter Product ID: ";
        cin >> id;

        auto it = inventory.find(id);

        if (it == inventory.end()) {
            cout << "\nProduct not found!\n";
            return;
        }

        cout << "Current Quantity: "
             << it->second.quantity << endl;

        cout << "Enter New Quantity: ";
        cin >> quantity;

        it->second.quantity = quantity;

        // Update vector
        for (auto &p : products) {
            if (p.id == id) {
                p.quantity = quantity;
                break;
            }
        }

        actionHistory.push(
            "Updated Stock of Product ID " + to_string(id)
        );

        cout << "\nStock updated successfully!\n";
    }


    // ================= DELETE PRODUCT =================

    void deleteProduct() {

        int id;

        cout << "\nEnter Product ID to delete: ";
        cin >> id;

        auto it = inventory.find(id);

        if (it == inventory.end()) {
            cout << "\nProduct not found!\n";
            return;
        }

        inventory.erase(id);

        // Delete from vector
        products.erase(
            remove_if(
                products.begin(),
                products.end(),
                [id](Product p) {
                    return p.id == id;
                }
            ),
            products.end()
        );

        actionHistory.push(
            "Deleted Product ID " + to_string(id)
        );

        cout << "\nProduct deleted successfully!\n";

        /*
            Note:
            For a college-level project, the hash map/vector
            are updated here. A complete production BST would
            also implement BST deletion.
        */
    }


    // ================= DISPLAY ALL PRODUCTS =================

    void displayAllProducts() {

        if (inventory.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        cout << "\n========== ALL PRODUCTS ==========\n";

        for (auto &p : products) {
            if (inventory.find(p.id) != inventory.end())
                p.display();
        }
    }


    // ================= DISPLAY SORTED =================

    void displaySorted() {

        if (inventory.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        cout << "\n====== PRODUCTS SORTED BY ID ======\n";

        inorder(root);
    }


    // ================= LOW STOCK PRODUCTS =================

    void lowStockProducts() {

        bool found = false;

        cout << "\n====== LOW STOCK PRODUCTS ======\n";

        for (auto &p : products) {

            if (inventory.find(p.id) != inventory.end()
                && p.quantity <= 5) {

                p.display();
                found = true;
            }
        }

        if (!found)
            cout << "\nNo low-stock products.\n";
    }


    // ================= RESTOCK REQUEST =================

    void requestRestock() {

        int id;

        cout << "\nEnter Product ID for restocking: ";
        cin >> id;

        if (inventory.find(id) == inventory.end()) {
            cout << "\nProduct not found!\n";
            return;
        }

        restockQueue.push(id);

        actionHistory.push(
            "Restock requested for Product ID "
            + to_string(id)
        );

        cout << "\nRestock request added to queue.\n";
    }


    // ================= PROCESS RESTOCK =================

    void processRestock() {

        if (restockQueue.empty()) {
            cout << "\nNo restock requests.\n";
            return;
        }

        int id = restockQueue.front();

        restockQueue.pop();

        int quantity;

        cout << "\nProcessing restock for Product ID: "
             << id << endl;

        cout << "Enter quantity to add: ";
        cin >> quantity;

        inventory[id].quantity += quantity;

        // Update vector
        for (auto &p : products) {

            if (p.id == id) {
                p.quantity += quantity;
                break;
            }
        }

        actionHistory.push(
            "Restocked Product ID "
            + to_string(id)
        );

        cout << "\nRestock completed successfully!\n";
    }


    // ================= SHOW ACTION HISTORY =================

    void showHistory() {

        if (actionHistory.empty()) {
            cout << "\nNo actions recorded.\n";
            return;
        }

        cout << "\n====== RECENT ACTIONS ======\n";

        stack<string> temp = actionHistory;

        while (!temp.empty()) {

            cout << "- "
                 << temp.top()
                 << endl;

            temp.pop();
        }
    }


    // ================= INVENTORY COUNT =================

    void showInventoryCount() {

        cout << "\nTotal Products: "
             << inventory.size()
             << endl;
    }


    // ================= MIDDLE PRODUCT =================

    void findMiddleProduct() {

        if (products.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        vector<Product> activeProducts;

        for (auto &p : products) {

            if (inventory.find(p.id) != inventory.end())
                activeProducts.push_back(p);
        }

        int n = activeProducts.size();

        int middle = n / 2;

        cout << "\n====== MIDDLE PRODUCT ======\n";

        activeProducts[middle].display();

        /*
            This demonstrates the middle element concept.

            For even number of products,
            the second middle element is displayed.
        */
    }
};


// ================= MAIN FUNCTION =================

int main() {

    InventorySystem system;

    int choice;

    cout << "========================================\n";
    cout << "     E-COMMERCE INVENTORY SYSTEM\n";
    cout << "========================================\n";


    do {

        cout << "\n\n========== MENU ==========\n";

        cout << "1. Add Product\n";
        cout << "2. Search Product\n";
        cout << "3. Update Stock\n";
        cout << "4. Delete Product\n";
        cout << "5. Display All Products\n";
        cout << "6. Display Products Sorted by ID\n";
        cout << "7. Show Low Stock Products\n";
        cout << "8. Request Restock\n";
        cout << "9. Process Restock\n";
        cout << "10. Show Action History\n";
        cout << "11. Show Total Products\n";
        cout << "12. Find Middle Product\n";
        cout << "13. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;


        switch (choice) {

        case 1:
            system.addProduct();
            break;

        case 2:
            system.searchProduct();
            break;

        case 3:
            system.updateStock();
            break;

        case 4:
            system.deleteProduct();
            break;

        case 5:
            system.displayAllProducts();
            break;

        case 6:
            system.displaySorted();
            break;

        case 7:
            system.lowStockProducts();
            break;

        case 8:
            system.requestRestock();
            break;

        case 9:
            system.processRestock();
            break;

        case 10:
            system.showHistory();
            break;

        case 11:
            system.showInventoryCount();
            break;

        case 12:
            system.findMiddleProduct();
            break;

        case 13:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 13);


    return 0;
}
