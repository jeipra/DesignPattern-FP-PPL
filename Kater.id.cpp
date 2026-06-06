#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SessionManager {
private:
    static SessionManager* instance;

    string currentUser;
    string currentRole;

    SessionManager() {}

public:

    static SessionManager* getInstance() {

        if(instance == nullptr) {
            instance = new SessionManager();
        }

        return instance;
    }

    void login(
        string username,
        string role)
    {
        currentUser = username;
        currentRole = role;

        cout << "\nLogin Berhasil" << endl;
        cout << "User : "
             << currentUser
             << endl;
    }

    string getCurrentUser() {
        return currentUser;
    }

    string getCurrentRole() {
        return currentRole;
    }

    void logout() {

        cout
        << "\nLogout Berhasil"
        << endl;

        currentUser = "";
        currentRole = "";
    }
};

SessionManager*
SessionManager::instance = nullptr;

class User {

protected:

    int idUser;
    string nama;
    string email;
    string noHp;
    string password;

public:

    User(
        int idUser,
        string nama,
        string email,
        string noHp,
        string password)
    {
        this->idUser = idUser;
        this->nama = nama;
        this->email = email;
        this->noHp = noHp;
        this->password = password;
    }

    virtual void tampilInfo() = 0;

    string getNama() {
        return nama;
    }
};

class Pelanggan : public User {

private:

    string preferensiMakanan;
    string alamat;

public:

    Pelanggan(
        int idUser,
        string nama,
        string email,
        string noHp,
        string password,
        string preferensiMakanan,
        string alamat)

    : User(
        idUser,
        nama,
        email,
        noHp,
        password)
    {
        this->preferensiMakanan =
            preferensiMakanan;

        this->alamat =
            alamat;
    }

    void tampilInfo() override {

        cout
        << "\n=== DATA PELANGGAN ==="
        << endl;

        cout
        << "Nama : "
        << nama
        << endl;

        cout
        << "Preferensi : "
        << preferensiMakanan
        << endl;

        cout
        << "Alamat : "
        << alamat
        << endl;
    }
};

class MitraUMKM : public User {

private:

    string namaToko;
    double saldo;
    bool statusVerifikasi;

public:

    MitraUMKM(
        int idUser,
        string nama,
        string email,
        string noHp,
        string password,
        string namaToko)

    : User(
        idUser,
        nama,
        email,
        noHp,
        password)
    {
        this->namaToko =
            namaToko;

        saldo = 0;
        statusVerifikasi = false;
    }

    void tampilInfo() override {

        cout
        << "\n=== DATA UMKM ==="
        << endl;

        cout
        << "Owner : "
        << nama
        << endl;

        cout
        << "Toko : "
        << namaToko
        << endl;
    }
};

class DriverKurir : public User {

private:

    string noKendaraan;

public:

    DriverKurir(
        int idUser,
        string nama,
        string email,
        string noHp,
        string password,
        string noKendaraan)

    : User(
        idUser,
        nama,
        email,
        noHp,
        password)
    {
        this->noKendaraan =
            noKendaraan;
    }

    void tampilInfo() override {

        cout
        << "\n=== DATA DRIVER ==="
        << endl;

        cout
        << "Nama : "
        << nama
        << endl;

        cout
        << "Kendaraan : "
        << noKendaraan
        << endl;
    }
};

class UserFactory {

public:

    static User*
    createUser(
        string role,
        string nama)
    {

        if(role == "Pelanggan") {

            return new Pelanggan(
                1,
                nama,
                "user@gmail.com",
                "08123",
                "123",
                "Vegan",
                "Surabaya"
            );
        }

        else if(role == "UMKM") {

            return new MitraUMKM(
                2,
                nama,
                "umkm@gmail.com",
                "08111",
                "123",
                "Healthy Food"
            );
        }

        else {

            return new DriverKurir(
                3,
                nama,
                "driver@gmail.com",
                "08199",
                "123",
                "L1234AB"
            );
        }
    }
};

class Observer {

public:

    virtual void update(
        string status) = 0;
};

class CustomerNotification
: public Observer {

private:

    string nama;

public:

    CustomerNotification(
        string nama)
    {
        this->nama = nama;
    }

    void update(
        string status)
        override
    {
        cout
        << "\n[Customer Notification]"
        << endl;

        cout
        << nama
        << " menerima update : "
        << status
        << endl;
    }
};

class UMKMNotification
: public Observer {

private:

    string nama;

public:

    UMKMNotification(
        string nama)
    {
        this->nama = nama;
    }

    void update(
        string status)
        override
    {
        cout
        << "\n[UMKM Notification]"
        << endl;

        cout
        << nama
        << " menerima update : "
        << status
        << endl;
    }
};

class DriverNotification
: public Observer {

private:

    string nama;

public:

    DriverNotification(
        string nama)
    {
        this->nama = nama;
    }

    void update(
        string status)
        override
    {
        cout
        << "\n[Driver Notification]"
        << endl;

        cout
        << nama
        << " menerima update : "
        << status
        << endl;
    }
};

class PaymentStrategy {

public:

    virtual void pay(
        double amount)=0;
};

class QRISPayment
: public PaymentStrategy {

public:

    void pay(
        double amount)
        override
    {
        cout
        << "\nPembayaran QRIS"
        << endl;

        cout
        << "Total : Rp "
        << amount
        << endl;
    }
};

class TransferBankPayment
: public PaymentStrategy {

public:

    void pay(
        double amount)
        override
    {
        cout
        << "\nTransfer Bank"
        << endl;

        cout
        << "Total : Rp "
        << amount
        << endl;
    }
};

class EWalletPayment
: public PaymentStrategy {

public:

    void pay(
        double amount)
        override
    {
        cout
        << "\nPembayaran E-Wallet"
        << endl;

        cout
        << "Total : Rp "
        << amount
        << endl;
    }
};

class Pembayaran {

private:

    PaymentStrategy*
    strategy;

public:

    void setStrategy(
        PaymentStrategy*
        strategy)
    {
        this->strategy =
            strategy;
    }

    void prosesPembayaran(
        double amount)
    {
        strategy->pay(amount);
    }
};

class PesananContext;

class OrderState {

public:

    virtual string
    getStatus() = 0;

    virtual void next(
        PesananContext*
    ) = 0;
};

class DiprosesUMKM;
class SiapDiambil;
class DalamPengiriman;
class Selesai;

class PesananContext {

private:

    OrderState* state;

public:

    PesananContext();

    void setState(
        OrderState* state)
    {
        this->state = state;
    }

    string getStatus()
    {
        return state->getStatus();
    }

    void nextState()
    {
        state->next(this);
    }
};

class MenungguPembayaran
: public OrderState {

public:

    string getStatus()
    {
        return "Menunggu Pembayaran";
    }

    void next(
        PesananContext*
    ) override;
};

class DiprosesUMKM
: public OrderState {

public:

    string getStatus()
    {
        return "Diproses UMKM";
    }

    void next(
        PesananContext*
    ) override;
};

class SiapDiambil
: public OrderState {

public:

    string getStatus()
    {
        return "Siap Diambil Driver";
    }

    void next(
        PesananContext*
    ) override;
};

class DalamPengiriman
: public OrderState {

public:

    string getStatus()
    {
        return "Dalam Pengiriman";
    }

    void next(
        PesananContext*
    ) override;
};

class Selesai
: public OrderState {

public:

    string getStatus()
    {
        return "Pesanan Selesai";
    }

    void next(
        PesananContext*
    ) override {}
};

class Menu {

private:

    int idMenu;
    string namaMenu;
    double harga;
    int stok;

public:

    Menu(
        int idMenu,
        string namaMenu,
        double harga,
        int stok)
    {
        this->idMenu = idMenu;
        this->namaMenu = namaMenu;
        this->harga = harga;
        this->stok = stok;
    }

    string getNamaMenu() {
        return namaMenu;
    }

    double getHarga() {
        return harga;
    }
};

class Rating {

private:

    int nilai;
    string komentar;

public:

    Rating(
        int nilai,
        string komentar)
    {
        this->nilai = nilai;
        this->komentar = komentar;
    }

    void tampilkan() {

        cout
        << "\nRating : "
        << nilai
        << "/5"
        << endl;

        cout
        << "Komentar : "
        << komentar
        << endl;
    }
};

class Komplain {

private:

    string jenis;
    string deskripsi;

public:

    Komplain(
        string jenis,
        string deskripsi)
    {
        this->jenis = jenis;
        this->deskripsi = deskripsi;
    }

    void tampilkan() {

        cout
        << "\nJenis Komplain : "
        << jenis
        << endl;

        cout
        << "Deskripsi : "
        << deskripsi
        << endl;
    }
};
class Pesanan {

private:

    int idPesanan;
    string tanggal;
    double totalHarga;

    vector<Menu> daftarMenu;

    vector<Observer*> observers;

    PesananContext statusPesanan;

public:

    Pesanan(
        int idPesanan,
        string tanggal)
    {
        this->idPesanan =
            idPesanan;

        this->tanggal =
            tanggal;

        totalHarga = 0;
    }

    void tambahMenu(
        Menu menu)
    {
        daftarMenu.push_back(
            menu);

        totalHarga +=
            menu.getHarga();
    }

    void addObserver(
        Observer* observer)
    {
        observers.push_back(
            observer);
    }

    void kirimNotifikasi()
    {
        for(
            Observer* observer
            : observers)
        {
            observer->update(
                statusPesanan
                .getStatus()
            );
        }
    }

    void updateStatus()
    {
        statusPesanan
        .nextState();

        kirimNotifikasi();
    }

    string getStatus()
    {
        return statusPesanan
            .getStatus();
    }

    double getTotalHarga()
    {
        return totalHarga;
    }

    void tampilkanPesanan()
    {
        cout
        << "\n===== DETAIL PESANAN ====="
        << endl;

        cout
        << "ID Pesanan : "
        << idPesanan
        << endl;

        cout
        << "Tanggal : "
        << tanggal
        << endl;

        cout
        << "\nDaftar Menu"
        << endl;

        for(Menu menu :
            daftarMenu)
        {
            cout
            << "- "
            << menu.getNamaMenu()
            << " | Rp "
            << menu.getHarga()
            << endl;
        }

        cout
        << "\nTotal Harga : Rp "
        << totalHarga
        << endl;

        cout
        << "Status : "
        << getStatus()
        << endl;
    }
};

void MenungguPembayaran::next(
    PesananContext* c)
{
    c->setState(
        new DiprosesUMKM()
    );
}

void DiprosesUMKM::next(
    PesananContext* c)
{
    c->setState(
        new SiapDiambil()
    );
}

void SiapDiambil::next(
    PesananContext* c)
{
    c->setState(
        new DalamPengiriman()
    );
}

void DalamPengiriman::next(
    PesananContext* c)
{
    c->setState(
        new Selesai()
    );
}

PesananContext::
PesananContext()
{
    state =
        new MenungguPembayaran();
}

void registerUser()
{
    string nama;
    string email;
    string password;

    cout
    << "\n===== REGISTER ====="
    << endl;

    cout
    << "Nama : ";
    cin >> nama;

    cout
    << "Email : ";
    cin >> email;

    cout
    << "Password : ";
    cin >> password;

    cout
    << "\nRegistrasi Berhasil"
    << endl;

    cout
    << "OTP Terkirim"
    << endl;

    cout
    << "Verifikasi Email Berhasil"
    << endl;
}

User* loginUser()
{
    string nama;

    cout
    << "\n===== LOGIN ====="
    << endl;

    cout
    << "Username : ";

    cin >> nama;

    SessionManager*
    session =
    SessionManager::
    getInstance();

    session->login(
        nama,
        "Pelanggan"
    );

    User* pelanggan =
        UserFactory::
        createUser(
            "Pelanggan",
            nama
        );

    return pelanggan;
}

void tampilMenu()
{
    cout
    << "\n===== MENU VEGAN ====="
    << endl;

    cout
    << "1. Vegan Bowl"
    << endl;

    cout
    << "2. Green Salad"
    << endl;

    cout
    << "3. Healthy Sandwich"
    << endl;

    cout
    << "4. Vegan Bento"
    << endl;
}

Pesanan buatPesanan()
{
    Menu menu1(
        1,
        "Vegan Bowl",
        25000,
        50
    );

    Menu menu2(
        2,
        "Green Salad",
        20000,
        50
    );

    Pesanan pesanan(
        1001,
        "2026-06-06"
    );

    pesanan.tambahMenu(
        menu1);

    pesanan.tambahMenu(
        menu2);

    return pesanan;
}

void prosesPembayaran(
    Pesanan& pesanan)
{
    int pilihan;

    cout
    << "\n===== PEMBAYARAN ====="
    << endl;

    cout
    << "1. QRIS"
    << endl;

    cout
    << "2. Transfer Bank"
    << endl;

    cout
    << "3. E-Wallet"
    << endl;

    cin >> pilihan;

    Pembayaran pembayaran;

    if(pilihan == 1)
    {
        QRISPayment qris;

        pembayaran
        .setStrategy(
            &qris);

        pembayaran
        .prosesPembayaran(
            pesanan
            .getTotalHarga()
        );
    }

    else if(
        pilihan == 2)
    {
        TransferBankPayment
        transfer;

        pembayaran
        .setStrategy(
            &transfer);

        pembayaran
        .prosesPembayaran(
            pesanan
            .getTotalHarga()
        );
    }

    else
    {
        EWalletPayment
        ewallet;

        pembayaran
        .setStrategy(
            &ewallet);

        pembayaran
        .prosesPembayaran(
            pesanan
            .getTotalHarga()
        );
    }
}

void trackingPesanan(
    Pesanan& pesanan)
{
    cout
    << "\n===== TRACKING PESANAN ====="
    << endl;

    cout
    << "Status Awal : "
    << pesanan.getStatus()
    << endl;

    pesanan.updateStatus();

    pesanan.updateStatus();

    pesanan.updateStatus();

    pesanan.updateStatus();
}

void beriRating()
{
    Rating rating(
        5,
        "Makanan sehat dan enak"
    );

    rating.tampilkan();
}

void kirimKomplain()
{
    Komplain komplain(
        "Pengiriman",
        "Kurir terlambat"
    );

    komplain.tampilkan();
}
void tampilProfile(User* user)
{
    cout << "\n===== PROFILE =====" << endl;

    user->tampilInfo();

    cout << "\nSession Aktif : "
         << SessionManager::
            getInstance()
            ->getCurrentUser()
         << endl;
}

void dashboardPelanggan()
{
    registerUser();

    User* pelanggan =
        loginUser();

    tampilProfile(
        pelanggan);

    tampilMenu();

    Pesanan pesanan =
        buatPesanan();

    CustomerNotification customer(
        pelanggan
        ->getNama());

    UMKMNotification umkm(
        "Healthy Food");

    DriverNotification driver(
        "Budi Driver");

    pesanan.addObserver(
        &customer);

    pesanan.addObserver(
        &umkm);

    pesanan.addObserver(
        &driver);

    pesanan
    .tampilkanPesanan();

    prosesPembayaran(
        pesanan);

    trackingPesanan(
        pesanan);

    beriRating();

    kirimKomplain();

    SessionManager::
    getInstance()
    ->logout();

    delete pelanggan;
}

int main()
{
    cout
    << "================================="
    << endl;

    cout
    << "      KATER.ID SYSTEM"
    << endl;

    cout
    << "================================="
    << endl;

    dashboardPelanggan();

    cout
    << "\nProgram Selesai"
    << endl;

    return 0;
}