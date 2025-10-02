#include <iostream>
#include <string>
using namespace std;

// Item class representing an individual item in the supermarket
class Item {
private:
  int itemID;
  string itemName;
  float price;
  int qty;

public:
  Item(int itemID, string itemName, float price, int qty) {
    this->itemID = itemID;
    this->itemName = itemName;
    this->price = price;
    this->qty = qty;
  }

  int getItemID() { return itemID; }

  string getItemName() { return itemName; }

  float getPrice() { return price; }

  int getQty() { return qty; }

  void setQty(int qty) { this->qty = qty; }

  void displayItem() {
    cout << "Item ID: " << itemID << " | Name: " << itemName << " | Price: $"
         << price << " | Stock: " << qty << endl;
  }

  Item() {} // default constuctor
};

// Linked List Node for storing Items
class ItemNode {
public:
  Item item;
  ItemNode *next;

  ItemNode(Item itm) {
    item = itm;
    next = NULL;
  }
};

void insertItem(ItemNode *&head, Item itm) {
  ItemNode *n = new ItemNode(itm);

  if (head == NULL) {
    head = n;
    return;
  }

  ItemNode *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = n;
}

void displayItems(ItemNode *head) {
  if (head == NULL) {
    cout << "No items available in the supermarket." << endl;
    return;
  }

  ItemNode *temp = head;
  while (temp != NULL) {
    temp->item.displayItem(); // Call the displayItem() method of Item class
    temp = temp->next;
  }
}

// linear search for finding item by its name
Item *linearSearch(ItemNode *head, string name) {
  ItemNode *temp = head;
  while (temp) {
    if (temp->item.getItemName() == name) {
      return &(temp->item);
    }
    temp = temp->next;
  }
  return nullptr;
}

// Convert linked list to array for sorting and binary search
void linklistToArray(ItemNode *head, Item arr[], int &size) {
  size = 0;
  ItemNode *temp = head;
  while (temp) {
    arr[size++] = temp->item;
    temp = temp->next;
  }
}

// bubble sort for sorting of array by itemID
void bubbleSort(Item arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j].getItemID() > arr[j + 1].getItemID()) {
        Item temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Binary Search for finding an item by itemID (for sorted array)
int binarySearch(Item arr[], int size, float targetID) {
  int left = 0, right = size - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid].getItemID() == targetID) {
      return mid;
    } else if (arr[mid].getItemID() < targetID) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

// Custom Cart class using array-based stack
class Cart {
private:
  int MAX_CART_SIZE = 100;
  Item cartStack[100]; // Array to store items
  int top;             // Index for the top item in the cart

public:
  Cart() {
    top = -1; // Initialize the top of the stack to -1
  }

  // Add item to the cart (push operation)
  void addItemToCart(Item itm) {
    if (top == MAX_CART_SIZE - 1) {
      cout << "cart is fulled" << endl;
      return;
    }
    top++;
    cartStack[top] = itm;
  }

  // Display all items in the cart
  void displayCart() {
    if (top == -1) {
      cout << "Cart is empty.\n";
      return;
    }
    for (int i = 0; i <= top; i++) {
      cartStack[i].displayItem(); // Display each item in the cart
    }
  }

  // Calculate total bill
  float calculateTotalBill() {
    float total = 0;
    for (int i = 0; i <= top; i++) {
      total += cartStack[i].getPrice(); // Sum the prices of all i                                                tems in the cart
    }
    return total;
  }
};

class CustomerQueue {
private:
  int MAX_QUEUE_SIZE = 100;
  string customerQueue[100]; // Array to store customer names
  int front;                 // Index for the front of the queue
  int back;                  // Index for the rear of the queue
  int count;                 // Number of customers in the queue

public:
  CustomerQueue() { // Initialize front, rear, and count
    front = -1;
    back = -1;
    count = 0;
  }

  // Add customer to the queue (enqueue operation)
  void addCustomer(string name) {
    if (back == MAX_QUEUE_SIZE - 1) {
      cout << "Queue is full! Cannot add more customers." << endl;
    } else {
      back++;
      customerQueue[back] = name;
      if (front == -1) {
        front++;
      }
      count++; // Increase the count of customers in the queue
      cout << "Customer '" << name << "' added to the queue.\n";
    }
  }

  // Process the next customer in the queue (dequeue operation)
  void processNextCustomer() {
    if (count > 0) {
      cout << "Processing bill for customer: " << customerQueue[front] << endl;
      front++; // increment for front
      count--; // Decrease the count of customers in the queue
    } else {
      cout << "No customers in the queue.\n";
    }
  }

  // Display all customers in the queue
  void displayQueue() {
    if (count == 0) {
      cout << "No customers in the queue." << endl;
      return;
    }
    cout << "Customers in the queue:" << endl;
    int idx = front;
    for (int i = 0; i < count; i++) {
      cout << customerQueue[idx] << endl;
      idx++;
    }
  }

  // Check if the queue is empty
  bool isEmpty() { return count == 0; }
};

// Function to display menu and get user choice
int displayMenu() {
  int choice;
  cout << "\n===== Supermarket Billing System Menu =====\n";
  cout << "1. Add Item to Supermarket\n";
  cout << "2. Display Supermarket Items\n";
  cout << "3. Search for Item by Name (Linear Search)\n";
  cout << "4. Add Item to Cart\n";
  cout << "5. Display Cart\n";
  cout << "6. Calculate Total Bill\n";
  cout << "7. Sort Items by itemID(bubble sort)\n";
  cout << "8. Search Item by itemID (Binary Search)\n";
  cout << "9. Add Customer to Queue\n";
  cout << "10. Process Customer Billing\n";
  cout << "11. Exit\n";
  cout << "Enter your choice: ";
  cin >> choice;
  return choice;
}
int main() {
  ItemNode *head = NULL;
  CustomerQueue customerQueue;
  Cart shoppingCart;
  int choice;
  do {
    choice = displayMenu();
    switch (choice) {
    case 1: {
      // Add Item to Supermarket
      int id, stock;
      string name;
      float price;
      cout << "Enter Item ID: ";
      cin >> id;
      cout << "Enter Item Name: ";
      cin >> name;
      cout << "Enter Price: ";
      cin >> price;
      cout << "Enter Stock Quantity: ";
      cin >> stock;
      insertItem(head, Item(id, name, price, stock));
      displayItems(head);
      cout << "Item added successfully.\n";
      break;
    }

    case 2: {
      // Display Supermarket Items
      cout << "\nSupermarket Items:\n";
      displayItems(head);
      break;
    }

    case 3: {
      // Search for Item by Name (Linear Search)
      string name;
      cout << "Enter Item Name to search: ";
      cin >> name;
      Item *foundItem = linearSearch(head, name);
      if (foundItem) {
        cout << "Item found:\n";
        foundItem->displayItem();
      } else {
        cout << "Item not found.\n";
      }
      break;
    }

    case 4: {
      // Add Item to Cart
      string name;
      cout << "Enter Item Name to add to cart: ";
      cin >> name;
      Item *foundItem = linearSearch(head, name);
      if (foundItem) {
        shoppingCart.addItemToCart(*foundItem);
        cout << "Item added to cart.\n";
      } else {
        cout << "Item not found.\n";
      }
      break;
    }

    case 5: {
      // Display Cart
      cout << "\nItems in Cart:\n";
      shoppingCart.displayCart();
      break;
    }

    case 6: {
      // Calculate Total Bill
      float total = shoppingCart.calculateTotalBill();
      cout << "Total Bill: $" << total << endl;
      break;
    }

    case 7: {
      // Sort Items by itemID
      int size = 0;
      Item itemArray[100];
      linklistToArray(head, itemArray, size);
      bubbleSort(itemArray, size);
      cout << "Items sorted by itemID:\n";
      for (int i = 0; i < size; i++) {
        itemArray[i].displayItem();
      }
      break;
    }

    case 8: {
      // Search Item by itemID (Binary Search)
      int itemID;
      cout << "Enter itemID to search: ";
      cin >> itemID;
      int size = 0;
      Item itemArray[100];
      linklistToArray(head, itemArray, size);
      bubbleSort(itemArray,
                 size); // Ensure array is sorted before binary search
      int index = binarySearch(itemArray, size, itemID);
      if (index != -1) {
        cout << "Item found:\n";
        itemArray[index].displayItem();
      } else {
        cout << "Item not found" << endl;
      }
      break;
    }

    case 9: {
      // Add Customer to Queue
      string customerName;
      cout << "Enter customer name: ";
      cin >> customerName;
      customerQueue.addCustomer(customerName);
      cout << "Customer added to queue.\n";
      break;
    }

    case 10: {
      // Process Customer Billing
      customerQueue.processNextCustomer();
      break;
    }

    case 11: {
      // Exit the program
      cout << "Exiting the system.\n";
      break;
    }

    default: {
      cout << "Invalid choice! Please try again.\n";
      break;
    }
    }
  } while (choice != 11);
  return 0;
}