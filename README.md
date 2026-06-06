# Final Project PPL

## Anggota Kelompok
| Nama           | NRP        | Kelas     |
| ---            | ---        | ----------|
| Jahhaza Assiqooyah Nurul Hidayah | 5025241019 | E |
| Nabilah Bunga Sulistia | 5025241073 | E |
| Jeihan Shawmy Prasetya | 5025241132 | E |
| Fathiya Nayla Husna Wibowo | 5025241204 | E |

# DESIGN PATTERN

## 1. Singleton Pattern

Singleton Pattern diterapkan pada class `SessionManager` yang berfungsi untuk mengelola sesi pengguna yang sedang login. Tujuan penggunaan pattern ini adalah memastikan bahwa hanya ada satu objek `SessionManager` yang aktif selama program berjalan. Hal ini terlihat dari atribut static instance yang digunakan untuk menyimpan satu-satunya objek dari class tersebut serta constructor yang dibuat private sehingga objek tidak dapat dibuat langsung dari luar class.

``class SessionManager {
private:
    static SessionManager* instance;
    SessionManager() {}
public:
    static SessionManager* getInstance() {
        if(instance == nullptr) {
            instance = new SessionManager();
        }
        return instance;
    }
};``

Penggunaan Singleton dilakukan melalui method `getInstance()` :
``SessionManager* session =
SessionManager::getInstance();``


##2. Factory Method Pattern
Factory Method Pattern diterapkan pada class `UserFactory` yang bertugas membuat objek pengguna sesuai dengan role yang dipilih. Pattern ini digunakan untuk menyembunyikan proses pembuatan objek sehingga client tidak perlu mengetahui detail constructor dari masing-masing class turunan User.

``class UserFactory {
public:
    static User*
    createUser(
        string role,
        string nama)
    {
        if(role == "Pelanggan") {
            return new Pelanggan(...);
        }
        else if(role == "UMKM") {
            return new MitraUMKM(...);
        }
        else {
            return new DriverKurir(...);
        }
    }
};``

Factory tersebut digunakan saat proses login:
``User* pelanggan =
    UserFactory::
    createUser(
        "Pelanggan",
        nama
    );``

##3. Observer Pattern
Observer Pattern digunakan untuk memberikan notifikasi kepada pelanggan, UMKM, dan driver ketika status pesanan berubah. Pada pola ini, class Pesanan bertindak sebagai subject yang menyimpan daftar observer, sedangkan `CustomerNotification`, `UMKMNotification`, dan `DriverNotification` bertindak sebagai observer.

``class Observer {
public:
    virtual void update(
        string status) = 0;
};``

Subject menyimpan daftar observer:
``vector<Observer*> observers;``

Observer ditambahkan menggunakan:

``void addObserver(
    Observer* observer)
{
    observers.push_back(
        observer);
}``

Proses pengiriman notifikasi dilakukan melalui:

``void kirimNotifikasi()
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
}``

Pendaftaran observer dilakukan pada dashboard pelanggan:

``pesanan.addObserver(
    &customer);
pesanan.addObserver(
    &umkm);
pesanan.addObserver(
    &driver);``

##4. Strategy Pattern

Strategy Pattern digunakan untuk menangani berbagai metode pembayaran yang tersedia pada sistem. Pola ini memungkinkan algoritma pembayaran diganti secara dinamis sesuai pilihan pengguna tanpa mengubah struktur utama program.

``class PaymentStrategy {
public:
    virtual void pay(
        double amount)=0;
};``

Implementasi strategi:
``class QRISPayment
: public PaymentStrategy {
public:
    void pay(
        double amount)
        override
    {
        cout
        << "\nPembayaran QRIS"
        << endl;
    }
};``

Context yang menggunakan strategy:
``class Pembayaran {
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
};``

Contoh penggunaan:

``QRISPayment qris;
pembayaran
.setStrategy(
    &qris);
pembayaran
.prosesPembayaran(
    pesanan.getTotalHarga()
);``


##5. State Pattern
State Pattern digunakan untuk mengelola perubahan status pesanan secara bertahap mulai dari menunggu pembayaran hingga pesanan selesai. Setiap status direpresentasikan oleh class yang berbeda sehingga perilaku masing-masing status dapat dipisahkan dengan jelas.

``class OrderState {
public:
    virtual string
    getStatus() = 0;
    virtual void next(
        PesananContext*
    ) = 0;
};``

- First State:
``class MenungguPembayaran
: public OrderState {
public:
    string getStatus()
    {
        return "Menunggu Pembayaran";
    }
    void next(
        PesananContext*
    ) override;
};``

- Transisi state:
``void MenungguPembayaran::next(
    PesananContext* c)
{
    c->setState(
        new DiprosesUMKM()
    );
}``

- Context yang menyimpan state aktif:
``class PesananContext {
private:
    OrderState* state;
public:
    void nextState()
    {
        state->next(this);
    }
};``

- Pemanggilan perubahan status:
``pesanan.updateStatus();``
