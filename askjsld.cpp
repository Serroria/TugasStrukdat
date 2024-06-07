#include <iostream>
#include <string>

using namespace std;

// Deklarasi struktur pengguna dan pembelian
struct User {
    string name;
    string phoneNumber;
    string NIK;
    User* next;

    User(const string& n, const string& p, const string& nik) : name(n), phoneNumber(p), NIK(nik), next(nullptr) {}
};

struct Purchase {
    string type;
    string package;
    double price;
    Purchase* next;

    Purchase(const string& t, const string& p, double pr) : type(t), package(p), price(pr), next(nullptr) {}
};

// Variabel global untuk menyimpan riwayat pembelian
Purchase* purchaseHistory = nullptr;

// Deklarasi fungsi
void addUser(User*& head, const string& name, const string& phoneNumber, const string& NIK);
User* findUser(User* head, const string& phoneNumber);
void displayPurchaseHistory();
void displayPackages(const string& type, const string& category);
double getPackagePrice(const string& type, const string& category, int choice);
string getPackageName(const string& type, const string& category, int choice);
void displayMainMenu();
void displayKuotaMenu();
void displayRegistrationMenu();
void addPurchase(Purchase*& head, const string& type, const string& package, double price);

int main() {
    User* userHead = nullptr;

    cout << "===========================" << endl;
    cout << "| Selamat datang di Telkom|" << endl;
    cout << "===========================" << endl;
    cout << "Masukkan *123# untuk mulai." << endl;

    string input;
    cin >> input;

    if (input != "*123#") {
        cout << "Kode salah. Silakan coba lagi." << endl;
        return 0;
    }

    displayRegistrationMenu();
    int regChoice;
    cin >> regChoice;

    string phoneNumber;
    string name, NIK;

    if (regChoice == 1) {
        cout << "Masukkan nomor telepon: ";
        cin >> phoneNumber;
        User* currentUser = findUser(userHead, phoneNumber);

        if (currentUser == nullptr) {
            cout << "Nomor tidak ditemukan. Silakan registrasi ulang." << endl;
            return 0;
        }
    } else if (regChoice == 2) {
        cout << "Silakan masukkan nama Anda: ";
        cin.ignore();
        getline(cin, name);
        cout << "Masukkan NIK: ";
        getline(cin, NIK);
        cout << "Masukkan nomor telepon: ";
        cin >> phoneNumber;

        addUser(userHead, name, phoneNumber, NIK);
    } else {
        cout << "Pilihan salah. Silakan coba lagi." << endl;
        return 0;
    }

    User* currentUser = findUser(userHead, phoneNumber);

    while (true) {
        displayMainMenu();
        int choice;
        cin >> choice;

        string purchaseType;
        if (choice == 1) {
            purchaseType = "pulsa";
            displayPackages(purchaseType, "");
            int packageChoice;
            cin >> packageChoice;

            if (packageChoice == 4) {
                continue; // Kembali ke menu utama
            }

            double price = getPackagePrice(purchaseType, "", packageChoice);
            string packageName = getPackageName(purchaseType, "", packageChoice);

            if (price == 0 || packageName == "") {
                cout << "Pilihan paket salah. Silakan coba lagi." << endl;
                continue;
            }

            string paymentMethod;
            cout << "Pilih metode pembayaran (contoh: Gopay, Ovo, Dana): ";
            cin >> paymentMethod;

            addPurchase(purchaseHistory, purchaseType, packageName, price);
            cout << "Pembelian berhasil. Terima kasih!" << endl;

            displayPurchaseHistory();
        } else if (choice == 2) {
            purchaseType = "kuota";
            displayKuotaMenu();
            int kuotaChoice;
            cin >> kuotaChoice;

            string kuotaCategory;
            if (kuotaChoice == 1) {
                kuotaCategory = "harian";
            } else if (kuotaChoice == 2) {
                kuotaCategory = "bulanan";
            } else if (kuotaChoice == 3) {
                kuotaCategory = "malam";
            } else if (kuotaChoice == 4) {
                continue; // Kembali ke menu utama
            } else {
                cout << "Pilihan salah. Silakan coba lagi." << endl;
                continue;
            }

            displayPackages(purchaseType, kuotaCategory);

            int packageChoice;
            cin >> packageChoice;

            if (packageChoice == 4) {
                continue; // Kembali ke menu utama
            }

            double price = getPackagePrice(purchaseType, kuotaCategory, packageChoice);
            string packageName = getPackageName(purchaseType, kuotaCategory, packageChoice);

            if (price == 0 || packageName == "") {
                cout << "Pilihan paket salah. Silakan coba lagi." << endl;
                continue;
            }

            string paymentMethod;
            cout << "Pilih metode pembayaran (contoh: Gopay, Ovo, Dana): ";
            cin >> paymentMethod;

            addPurchase(purchaseHistory, purchaseType, packageName, price);
            cout << "Pembelian berhasil. Terima kasih!" << endl;

            displayPurchaseHistory();
        } else if (choice == 3) {
            cout << "Terima kasih. Sampai jumpa lagi!" << endl;
            break;
        } else {
            cout << "Pilihan salah. Silakan coba lagi." << endl;
            continue;
        }
    }

    // Menghapus memori yang dialokasikan untuk pengguna dan pembelian
    User* current = userHead;
    while (current != nullptr) {
        User* temp = current;
        current = current->next;
        delete temp;
    }

    Purchase* currentPurchase = purchaseHistory;
    while (currentPurchase != nullptr) {
        Purchase* temp = currentPurchase;
        currentPurchase = currentPurchase->next;
        delete temp;
    }

    return 0;
}

void addUser(User*& head, const string& name, const string& phoneNumber, const string& NIK) {
    User* newUser = new User(name, phoneNumber, NIK);
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

User* findUser(User* head, const string& phoneNumber) {
    User* current = head;
    while (current != nullptr) {
        if (current->phoneNumber == phoneNumber) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void addPurchase(Purchase*& head, const string& type, const string& package, double price) {
    Purchase* newPurchase = new Purchase(type, package, price);
    if (head == nullptr) {
        head = newPurchase;
    } else {
        Purchase* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPurchase;
    }
}

void displayPurchaseHistory() {
    cout << "\n=== Riwayat Pembelian ===" << endl;
    Purchase* current = purchaseHistory;
    while (current != nullptr) {
        cout << "Jenis: " << current->type << ", Paket: " << current->package << ", Harga: Rp" << current->price << endl;
        current = current->next;
    }
    cout << "=========================" << endl;
}

void displayPackages(const string& type, const string& category) {
    if (type == "pulsa") {
        cout << "\n=== Pilih Paket Pulsa ===" << endl;
        cout << "1. Rp10,000" << endl;
        cout << "2. Rp20,000" << endl;
        cout << "3. Rp50,000" << endl;
        cout << "4. Kembali" << endl;
    } else if (type == "kuota") {
        if (category == "harian") {
            cout << "\n=== Pilih Paket Kuota Harian ===" << endl;
            cout << "1. 500MB - Rp2,000" << endl;
            cout << "2. 1GB - Rp3,000" << endl;
            cout << "3. 2GB - Rp5,000" << endl;
            cout << "4. Kembali" << endl;
        } else if (category == "bulanan") {
            cout << "\n=== Pilih Paket Kuota Bulanan ===" << endl;
            cout << "1. 5GB - Rp25,000" << endl;
            cout << "2. 10GB - Rp40,000" << endl;
            cout << "3. 20GB - Rp75,000" << endl;
            cout << "4. Kembali" << endl;
        } else if (category == "malam") {
            cout << "\n=== Pilih Paket Kuota Malam ===" << endl;
            cout << "1. 1GB - Rp5,000" << endl;
            cout << "2. 5GB - Rp15,000" << endl;
            cout << "3. 10GB - Rp25,000" << endl;
            cout << "4. Kembali" << endl;
        }
    }
}

double getPackagePrice(const string& type, const string& category, int choice) {
    if (type == "pulsa") {
        if (choice == 1) return 10000;
        if (choice == 2) return 20000;
        if (choice == 3) return 50000;
        if (choice == 4) return 0;
    } else if (type == "kuota") {
        if (category == "harian") {
            if (choice == 1) return 2000;
            if (choice == 2) return 3000;
            if (choice == 3) return 5000;
            if (choice == 4) return 0;
        } else if (category == "bulanan") {
            if (choice == 1) return 25000;
            if (choice == 2) return 40000;
            if (choice == 3) return 75000;
            if (choice == 4) return 0;
        } else if (category == "malam") {
            if (choice == 1) return 5000;
            if (choice == 2) return 15000;
            if (choice == 3) return 25000;
            if (choice == 4) return 0;
        }
    }
    return 0;
}

string getPackageName(const string& type, const string& category, int choice) {
    if (type == "pulsa") {
        if (choice == 1) return "Rp10,000";
        if (choice == 2) return "Rp20,000";
        if (choice == 3) return "Rp50,000";
    } else if (type == "kuota") {
        if (category == "harian") {
            if (choice == 1) return "500MB - Rp2,000";
            if (choice == 2) return "1GB - Rp3,000";
            if (choice == 3) return "2GB - Rp5,000";
        } else if (category == "bulanan") {
            if (choice == 1) return "5GB - Rp25,000";
            if (choice == 2) return "10GB - Rp40,000";
            if (choice == 3) return "20GB - Rp75,000";
        } else if (category == "malam") {
            if (choice == 1) return "1GB - Rp5,000";
            if (choice == 2) return "5GB - Rp15,000";
            if (choice == 3) return "10GB - Rp25,000";
        }
    }
    return "";
}

void displayMainMenu() {
    cout << "\n=== Menu Utama ===" << endl;
    cout << "1. Pulsa" << endl;
    cout << "2. Kuota" << endl;
    cout << "3. Keluar" << endl;
    cout << "==================" << endl;
    cout << "Masukkan pilihan Anda: ";
}

void displayKuotaMenu() {
    cout << "\n=== Pilih Jenis Kuota ===" << endl;
    cout << "1. Kuota Harian" << endl;
    cout << "2. Kuota Bulanan" << endl;
    cout << "3. Kuota Malam" << endl;
    cout << "4. Kembali" << endl;
    cout << "========================" << endl;
    cout << "Masukkan pilihan Anda: ";
}

void displayRegistrationMenu() {
    cout << "\n=== Menu Registrasi ===" << endl;
    cout << "1. Saya sudah memiliki akun" << endl;
    cout << "2. Saya belum memiliki akun" << endl;
    cout << "========================" << endl;
    cout << "Masukkan pilihan Anda: ";
}
