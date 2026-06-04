#include <iostream>
#include <string>
#include <vector>
using namespace std;


// ============================================================
// REVIEW CLASS
// ============================================================

class Review
{
private:
    int rating;

public:
    Review(int rating)
    {
        this->rating = rating;
    }

    void display()
    {
        cout << "Rating  : " << rating << "/5" << endl;
    }

    int getRating()
    {
        return rating;
    }
};


// ============================================================
// SERVICE WORKER CLASS (base / abstract)
// ============================================================

class ServiceWorker
{
protected:
    string id;
    string name;
    string phone;
    string city;
    float  rating;
    int    totalReviews;

public:
    ServiceWorker(string id, string name, string phone, string city)
    {
        this->id           = id;
        this->name         = name;
        this->phone        = phone;
        this->city         = city;
        this->rating       = 0;
        this->totalReviews = 0;
    }

    virtual ~ServiceWorker() {}

    virtual double calculateRate() = 0;
    virtual string getCategory()   = 0;

    void addReview(Review r)
    {
        rating = (rating * totalReviews + r.getRating()) / (totalReviews + 1);
        totalReviews++;
        cout << "Review submitted!" << endl;
    }

    void displayInfo()
    {
        cout << "------------------------------" << endl;
        cout << "ID       : " << id                  << endl;
        cout << "Name     : " << name                << endl;
        cout << "Category : " << getCategory()       << endl;
        cout << "City     : " << city                << endl;
        cout << "Phone    : " << phone               << endl;
        cout << "Rating   : " << rating << "/5"      << endl;
        cout << "Rate     : PKR " << calculateRate() << endl;
    }

    string getId()   { return id; }
    string getName() { return name; }
};


// ============================================================
// DERIVED WORKER CLASSES
// ============================================================

class ElectricianWorker : public ServiceWorker
{
public:
    ElectricianWorker(string id, string name, string phone, string city)
        : ServiceWorker(id, name, phone, city)
    {
    }

    double calculateRate()
    {
        return 1000.0;
    }

    string getCategory()
    {
        return "Electrician";
    }
};


class PlumberWorker : public ServiceWorker
{
public:
    PlumberWorker(string id, string name, string phone, string city)
        : ServiceWorker(id, name, phone, city)
    {
    }

    double calculateRate()
    {
        return 700.0;
    }

    string getCategory()
    {
        return "Plumber";
    }
};


class ACTechWorker : public ServiceWorker
{
public:
    ACTechWorker(string id, string name, string phone, string city)
        : ServiceWorker(id, name, phone, city)
    {
    }

    double calculateRate()
    {
        return 1500.0;
    }

    string getCategory()
    {
        return "AC Technician";
    }
};


// ============================================================
// USER CLASS
// ============================================================

class User
{
private:
    string name;
    string email;
    string password;
    string phone;
    vector<string> bookingHistory;

public:
    User(string name, string email, string password, string phone)
    {
        this->name     = name;
        this->email    = email;
        this->password = password;
        this->phone    = phone;
    }

    bool login(string email, string password)
    {
        if (this->email == email && this->password == password)
            return true;
        return false;
    }

    void addBooking(string bookingId)
    {
        bookingHistory.push_back(bookingId);
    }

    void viewHistory()
    {
        if (bookingHistory.size() == 0)
        {
            cout << "No bookings yet." << endl;
            return;
        }
        cout << "Your Booking IDs: ";
        for (int i = 0; i < bookingHistory.size(); i++)
        {
            cout << bookingHistory[i] << "  ";
        }
        cout << endl;
    }

    string getName()  { return name; }
    string getEmail() { return email; }
};


// ============================================================
// BOOKING CLASS
// ============================================================

class Booking
{
private:
    string         bookingId;
    User*          customer;
    ServiceWorker* worker;
    string         date;
    double         price;
    static int     counter;

public:
    Booking(User* customer, ServiceWorker* worker, string date)
    {
        this->customer  = customer;
        this->worker    = worker;
        this->date      = date;
        this->price     = worker->calculateRate();
        counter++;
        this->bookingId = "BK" + to_string(counter);
    }

    void display()
    {
        cout << "------------------------------" << endl;
        cout << "Booking ID : " << bookingId           << endl;
        cout << "Customer   : " << customer->getName() << endl;
        cout << "Worker     : " << worker->getName()   << endl;
        cout << "Date       : " << date                << endl;
        cout << "Price      : PKR " << price           << endl;
    }

    string         getBookingId() { return bookingId; }
    ServiceWorker* getWorker()    { return worker; }
};

int Booking::counter = 100;


// ============================================================
// GLOBAL DATA
// ============================================================

vector<User*>          users;
vector<ServiceWorker*> workers;
vector<Booking*>       bookings;
User* loggedInUser = NULL;


// ============================================================
// FUNCTIONS
// ============================================================

void loadSampleWorkers()
{
    workers.push_back(new ElectricianWorker("W1", "Asif Khan",   "0311-1234567", "Abbottabad"));
    workers.push_back(new PlumberWorker    ("W2", "Tariq Ahmed", "0322-9876543", "Abbottabad"));
    workers.push_back(new ACTechWorker     ("W3", "Bilal Tech",  "0333-5556677", "Abbottabad"));
}


void showWorkers()
{
    cout << "\n--- Available Workers ---" << endl;
    for (int i = 0; i < workers.size(); i++)
    {
        workers[i]->displayInfo();
    }
}


void registerUser()
{
    string name, email, password, phone;

    cout << "\n--- Register ---" << endl;
    cout << "Name     : "; getline(cin >> ws, name);
    cout << "Email    : "; cin >> email;
    cout << "Password : "; cin >> password;
    cout << "Phone    : "; cin >> phone;

    users.push_back(new User(name, email, password, phone));
    cout << "Account created. Please login." << endl;
}


void loginUser()
{
    string email, password;

    cout << "\n--- Login ---" << endl;
    cout << "Email    : "; cin >> email;
    cout << "Password : "; cin >> password;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->login(email, password) == true)
        {
            loggedInUser = users[i];
            cout << "Welcome, " << users[i]->getName() << "!" << endl;
            return;
        }
    }

    cout << "Incorrect email or password." << endl;
}


void makeBooking()
{
    if (loggedInUser == NULL)
    {
        cout << "Please login first." << endl;
        return;
    }

    showWorkers();

    string wid;
    cout << "\nEnter Worker ID: ";
    cin >> wid;

    ServiceWorker* chosen = NULL;
    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i]->getId() == wid)
        {
            chosen = workers[i];
            break;
        }
    }

    if (chosen == NULL)
    {
        cout << "Worker not found." << endl;
        return;
    }

    string date;
    cout << "Enter date (e.g. 2025-12-01): ";
    cin >> date;

    Booking* b = new Booking(loggedInUser, chosen, date);
    cout << "Booking confirmed!" << endl;
    b->display();

    loggedInUser->addBooking(b->getBookingId());
    bookings.push_back(b);
}


void viewMyBookings()
{
    if (loggedInUser == NULL)
    {
        cout << "Please login first." << endl;
        return;
    }

    cout << "\n--- Your Bookings ---" << endl;
    loggedInUser->viewHistory();

    for (int i = 0; i < bookings.size(); i++)
    {
        bookings[i]->display();
    }
}


void leaveReview()
{
    if (loggedInUser == NULL)
    {
        cout << "Please login first." << endl;
        return;
    }

    string bid;
    cout << "Enter Booking ID: ";
    cin >> bid;

    for (int i = 0; i < bookings.size(); i++)
    {
        if (bookings[i]->getBookingId() == bid)
        {
            int r;
            cout << "Rating (1-5): ";
            cin >> r;

            Review rev(r);
            bookings[i]->getWorker()->addReview(rev);
            return;
        }
    }
    cout << "Booking not found." << endl;
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    loadSampleWorkers();

    cout << "==============================" << endl;
    cout << "   FIXR - Home Services App   " << endl;
    cout << "==============================" << endl;

    int choice;

    do
    {
        cout << "\n--- Main Menu ---"  << endl;
        cout << "1. Register"         << endl;
        cout << "2. Login"            << endl;
        cout << "3. Browse Workers"   << endl;
        cout << "4. Make a Booking"   << endl;
        cout << "5. View My Bookings" << endl;
        cout << "6. Leave a Review"   << endl;
        cout << "0. Exit"             << endl;
        cout << "Choice: ";
        cin  >> choice;

        if (choice == 1)
            registerUser();
        else if (choice == 2)
            loginUser();
        else if (choice == 3)
            showWorkers();
        else if (choice == 4)
            makeBooking();
        else if (choice == 5)
            viewMyBookings();
        else if (choice == 6)
            leaveReview();
        else if (choice == 0)
            cout << "Goodbye!" << endl;
        else
            cout << "Invalid option." << endl;

    } while (choice != 0);

    for (int i = 0; i < users.size();    i++) delete users[i];
    for (int i = 0; i < workers.size();  i++) delete workers[i];
    for (int i = 0; i < bookings.size(); i++) delete bookings[i];

    return 0;
}