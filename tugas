#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Deklarasi struktur pengguna dan pembelian
struct User {
    string name;
    int phoneNumber;
    User* next;

    User(const string& n, int p) : name(n), phoneNumber(p), next(nullptr) {}
};

struct Purchase {
    string type;
    string package;
    double price;
};

// Variabel global untuk menyimpan riwayat pembelian
vector<Purchase> purchaseHistory;

// Deklarasi fungsi
void addUser(User*& head, const string& name, int phoneNumber);
User* findUser(User* head, int phoneNumber);
void displayPurchaseHistory();
void displayPackages(const string& type);
double getPackagePrice(const string& type, int choice);
string getPackageName(const string& type, int choice);

int main() {
    User* userHead = nullptr;

    cout << "Selamat datang di Telsamsul, masukkan *123# untuk mulai." << endl;
    string input;
    cin >> input;

    if (input != "*123#") {
        cout << "Kode salah. Silakan coba lagi." << endl;
        return 0;
    }

    int phoneNumber;
    cout << "Masukkan nomor telepon: ";
    cin >> phoneNumber;

    User* currentUser = findUser(userHead, phoneNumber);
   

    while (true) {
        int choice;
        cout << "\nPilih jenis pembelian:" << endl;
        cout << "1. Pulsa" << endl;
        cout << "2. Kuota" << endl;
        cout << "3. Keluar" << endl;
        cin >> choice;

        string purchaseType;
        if (choice == 1) {
            purchaseType = "pulsa";
        } else if (choice == 2) {
            purchaseType = "kuota";
        } else if (choice == 3) {
            cout << "Terima kasih. Sampai jumpa lagi!" << endl;
            break;
        } else {
            cout << "Pilihan salah. Silakan coba lagi." << endl;
            continue;
        }

        displayPackages(purchaseType);

        int packageChoice;
        cin >> packageChoice;

        double price = getPackagePrice(purchaseType, packageChoice);
        string packageName = getPackageName(purchaseType, packageChoice);

        if (price == 0 || packageName == "") {
            cout << "Pilihan paket salah. Silakan coba lagi." << endl;
            continue;
        }

        string paymentMethod;
        cout << "Pilih metode pembayaran (contoh: Gopay, Ovo, Dana): ";
        cin >> paymentMethod;

        purchaseHistory.push_back({purchaseType, packageName, price});
        cout << "Pembelian berhasil. Terima kasih!" << endl;

        displayPurchaseHistory();
    }

    // Menghapus memori yang dialokasikan untuk pengguna
    User* current = userHead;
    while (current != nullptr) {
        User* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}

// Implementasi fungsi-fungsi deklarasi
void addUser(User*& head, const string& name, int phoneNumber) {
    User* newUser = new User(name, phoneNumber);
    if (head == nullptr) {
        head = newUser;
    } else {
        User* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
}

User* findUser(User* head, int phoneNumber) {
    User* current = head;
    while (current != nullptr) {
        if (current->phoneNumber == phoneNumber) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void displayPurchaseHistory() {
    cout << "Riwayat Pembelian:" << endl;
    for (const auto& purchase : purchaseHistory) {
        cout << "Jenis: " << purchase.type << ", Paket: " << purchase.package << ", Harga: Rp" << purchase.price << endl;
    }
}

void displayPackages(const string& type) {
    if (type == "pulsa") {
        cout << "Pilih paket pulsa:" << endl;
        cout << "1. Rp10,000" << endl;
        cout << "2. Rp20,000" << endl;
        cout << "3. Rp50,000" << endl;
        cout << "4. Kembali" << endl;
    } else if (type == "kuota") {
        cout << "Pilih paket kuota:" << endl;
        cout << "1. 1GB - Rp10,000" << endl;
        cout << "2. 5GB - Rp25,000" << endl;
        cout << "3. 10GB - Rp40,000" << endl;
        cout << "4. Kembali" << endl;
    }
}

double getPackagePrice(const string& type, int choice) {
    if (type == "pulsa") {
        if (choice == 1) return 10000;
        if (choice == 2) return 20000;
        if (choice == 3) return 50000;
        if (choice == 4) return choice;
    } else if (type == "kuota") {
        if (choice == 1) return 10000;
        if (choice == 2) return 25000;
        if (choice == 3) return 40000;
        if (choice == 4) return choice;
    }
    return 0;
}

string getPackageName(const string& type, int choice) {
    if (type == "pulsa") {
        if (choice == 1) return "Rp10,000";
        if (choice == 2) return "Rp20,000";
        if (choice == 3) return "Rp50,000";
        
    } else if (type == "kuota") {
        if (choice == 1) return "1GB - Rp10,000";
        if (choice == 2) return "5GB - Rp25,000";
        if (choice == 3) return "10GB - Rp40,000";
       
    }
    return "";
}
