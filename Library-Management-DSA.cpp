#include <iostream>
#include <queue>
using namespace std;

// Node structure for the BST
struct Book {
    int isbn;
    string title;
    string author;
    Book* left;
    Book* right;

    // Constructor to initialize a book
    Book(int i, string t, string a) : isbn(i), title(t), author(a), left(nullptr), right(nullptr) {}
};

// Library class to manage the BST
class Library {
private:
    Book* root;

    // Helper function to insert a book into the BST
    Book* insert(Book* node, int isbn, string title, string author) {
        if (!node) return new Book(isbn, title, author);
        if (isbn < node->isbn)
            node->left = insert(node->left, isbn, title, author);
        else if (isbn > node->isbn)
            node->right = insert(node->right, isbn, title, author);
        return node;
    }

    // Helper function to search for a book by ISBN
    Book* search(Book* node, int isbn) {
        if (!node || node->isbn == isbn) return node;
        if (isbn < node->isbn)
            return search(node->left, isbn);
        else
            return search(node->right, isbn);
    }

    // Helper function to find the minimum value node
    Book* findMin(Book* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    // Helper function to delete a book by ISBN
    Book* deleteBook(Book* node, int isbn) {
        if (!node) return nullptr;

        if (isbn < node->isbn) {
            node->left = deleteBook(node->left, isbn);
        } else if (isbn > node->isbn) {
            node->right = deleteBook(node->right, isbn);
        } else {
            // Node with one child or no child
            if (!node->left) {
                Book* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Book* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Book* temp = findMin(node->right);
            node->isbn = temp->isbn;
            node->title = temp->title;
            node->author = temp->author;
            node->right = deleteBook(node->right, temp->isbn);
        }
        return node;
    }

    // Helper function for in-order traversal
    void inOrder(Book* node) {
        if (node) {
            inOrder(node->left);
            cout << "ISBN: " << node->isbn << ", Title: " << node->title << ", Author: " << node->author << endl;
            inOrder(node->right);
        }
    }
   
    // Helper function to count total books
    int countBooks(Book* node) {
        if (!node) return 0;
        return 1 + countBooks(node->left) + countBooks(node->right);
    }

    // Helper function to find the smallest ISBN
    Book* findSmallest(Book* node) {
        return findMin(node);
    }

    // Helper function to find the largest ISBN
    Book* findLargest(Book* node) {
        while (node && node->right) node = node->right;
        return node;
    }

public:
    Library() : root(nullptr) {}

    void insertBook(int isbn, string title, string author) {
        root = insert(root, isbn, title, author);
    }

    void searchBook(int isbn) {
        Book* result = search(root, isbn);
        if (result) {
            cout << "Book found: ISBN: " << result->isbn << ", Title: " << result->title << ", Author: " << result->author << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }

    void deleteBook(int isbn) {
        root = deleteBook(root, isbn);
    }

    void displayBooksInOrder() {
        cout << "Books in ascending order of ISBN:" << endl;
        inOrder(root);
    }

    void displayBooksLevelOrder() {
        cout << "Books in level-order:" << endl;
        //levelOrder(root);
    }
 
    void countTotalBooks() {
        cout << "Total number of books: " << countBooks(root) << endl;
    }

    void findOldestAndNewest() {
        Book* oldest = findSmallest(root);
        Book* newest = findLargest(root);
        if (oldest && newest) {
            cout << "Oldest Book: ISBN: " << oldest->isbn << endl;
            cout << "Newest Book: ISBN: " << newest->isbn << endl;
        } else {
            cout << "No books in the library!" << endl;
        }
    }
    void levelOrder(Book* node) {
        if (!node) return;
        queue<Book*> q;
        q.push(node);
        while (!q.empty()) {
            Book* current = q.front();
            q.pop();
            cout << "ISBN: " << current->isbn << ", Title: " << current->title << ", Author: " << current->author << endl;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

};

// Main function
int main() {
    Library library;
    library.insertBook(101, "C++ Programming", "Bjarne Stroustrup");
    library.insertBook(102, "Data Structures", "Mark Allen Weiss");
    library.insertBook(100, "Introduction to Algorithms", "Thomas H. Cormen");
    library.displayBooksInOrder();
    library.searchBook(101);
    library.deleteBook(102);
    library.displayBooksInOrder();
    library.countTotalBooks();
    library.findOldestAndNewest();

    return 0;
}
