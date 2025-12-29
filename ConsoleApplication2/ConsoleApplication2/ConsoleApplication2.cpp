#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_CURRENCIES = 50;
const char FILE_NAME[] = "currency.dat";

struct Currency {
    char name[30];
    char isoCode[10];
    double sellRate;
    double buyRate;
    double available;
    double maxTransaction;
    bool isTraded;
};

void showMenu() {
    cout << "=== ОБМЕННО МЕНЮ 1 ===" << endl;
    cout << "1. Добавяне на валути" << endl;
    cout << "2. Извеждане на всички валути" << endl;
    cout << "3. Търсене" << endl;
    cout << "4. Подреждане" << endl;
    cout << "5. Управление на файл" << endl;
    cout << "6. Допълнително меню 2" << endl;
    cout << "7. Покупко-продажба" << endl;
    cout << "0. Изход" << endl;
    cout << "Избор: " << endl;
}

void searchAndshowMenu() {
    cout << "=== Меню за търсене и извеждане ===" << endl;
    cout << "1. Търсене по най-ниска наличност" << endl;
    cout << "2. Търсене по ISO код" << endl;
    cout << "0. Назад" << endl;
}

void secondFuncMenu() {
    cout << "=== ОБМЕННО МЕНЮ 2 ===" << endl;
    cout << "1. Извеждане на валутите, които се търгуват" << endl;
    cout << "2. Търсене на валути по въведена от клавиатурата стойност" << endl;
    cout << "0. Назад" << endl;;
}

void purchaseSaleMenu() {
    cout << "=== МЕНЮ ЗА ПОКУПКО/ПРОДАЖБА ===" << endl;
    cout << "1. Покупка на валута" << endl;;
    cout << "2. Продажба на валута" << endl;
    cout << "0. Назад" << endl;
}

void printInfoCurr(const Currency& c)
{
    cout << "Име: " << c.name << " ---- " << endl
        << "ISO код: " << c.isoCode << " ---- " << endl
        << "Курс продава: " << c.sellRate << " ---- "
        << "Курс купува: " << c.buyRate << " ---- " << endl
        << "Наличност: " << c.available << " ---- " << endl
        << "Макс. сума за транзакция: " << c.maxTransaction << " ---- " << endl
        << "Търгува ли се: " << (c.isTraded ? "Да" : "Не") << "\n" << endl;

}

void addCurrencies(Currency currencies[], unsigned int& currencyCount) {

    int newCurrencies;

    cout << "Колко валути искате да добавите?" << endl;
    cin >> newCurrencies;

    if (currencyCount + newCurrencies > MAX_CURRENCIES) {
        cout << "Надвишавате максималния брой от 50 валути!" << endl;
        return;
    }

    for (int i = 0; i < newCurrencies; i++) {
        Currency c;
        int traded;

        cout << "Валута #" << currencyCount + 1 << ":" << endl;
        cout << "Наименование: "; cin >> c.name;
        cout << "Код по ISO: "; cin >> c.isoCode;
        cout << "Курс продава: "; cin >> c.sellRate;
        cout << "Курс купува: "; cin >> c.buyRate;
        cout << "Наличност: "; cin >> c.available;
        cout << "Макс. сума за транзакция: "; cin >> c.maxTransaction;
        cout << "Търгува ли се (1=Да / 0=Не): "; cin >> traded;

        if (traded == 1) {
            c.isTraded = true;
        }
        else {
            c.isTraded = false;
        }

        currencies[currencyCount] = c;
        currencyCount++;

        cout << "Валутата беше добавена!\n" << endl;
    }
}

void displayCurrencies(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути." << endl;
        return;
    }

    cout << "=== Списък с валути ===" << endl;

    for (int i = 0; i < count; i++) {
        printInfoCurr(currencies[i]);
    }

    cout << "=== Край на списъка с валути ===" << endl;
}

void findLowestAvailability(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути.\n";
        return;
    }

    int idx = 0;

    for (int i = 1; i < count; i++) {
        if (currencies[i].available < currencies[idx].available)
            idx = i;
    }

    printInfoCurr(currencies[idx]);
}

int findByISOCurrencyreturn(const Currency currencies[], const unsigned int count, const string& iso) {
    for (int i = 0; i < count; i++) {
        if (currencies[i].isoCode == iso) return i;
    }
    return -1;
}

void findByISO(const Currency currencies[], const unsigned int count, const string& reqIsoCode) {

    if (count == 0) {
        cout << "Няма добавени валути.\n";
        return;
    }

    int res = findByISOCurrencyreturn(currencies, count, reqIsoCode);

    if (res != -1)
    {
        printInfoCurr(currencies[res]);
        return;
    }

    cout << "Няма валута с този ISO код.\n";
}

void sortTheMainArray(Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути.\n";
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            double marginA = currencies[j].sellRate - currencies[j].buyRate;
            double marginB = currencies[j + 1].sellRate - currencies[j + 1].buyRate;

            if (marginA < marginB) {
                swap(currencies[j], currencies[j + 1]);
            }
        }
    }

    cout << "Валутите бяха подредени в намаляващ ред според маржа.\n" << endl;
}

void saveToFile(const Currency currencies[], const unsigned int count)
{
    ofstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Грешка при отваряне на файла за запис!\n";
        return;
    }

    file.write((char*)&count, sizeof(count));
    file.write((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Данните са записани във файла.\n";
}

void loadFromFile(Currency currencies[], unsigned int& count)
{
    ifstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Файлът не съществува. Стартиране с празен списък.\n";
        count = 0;
        return;
    }

    file.read((char*)&count, sizeof(count));
    file.read((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Данните са заредени от файла.\n";
}

void showTradedSortedByName(Currency currencies[], const unsigned int count) {

    Currency temp[50];
    int tCount = 0;

    for (int i = 0; i < count; i++) {
        if (currencies[i].isTraded)
            temp[tCount++] = currencies[i];
    }

    if (tCount == 0)
    {
        cout << "Няма налични валути!" << endl;
        return;
    }

    for (int i = 0; i < tCount - 1; i++) {
        for (int j = 0; j < tCount - i - 1; j++) {
            if (strcmp(temp[j].name, temp[j + 1].name) > 0) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    for (int i = 0; i < tCount; i++) {
        printInfoCurr(temp[i]);
    }
}

void findByAvailabilityAndMargin(const Currency currencies[], const unsigned int count, const double minAvailable, double const maxMarginPercent)
{
    bool found = false;

    for (int i = 0; i < count; i++) {
        double marginPercent = ((currencies[i].sellRate - currencies[i].buyRate)
            / currencies[i].buyRate) * 100.0;

        if (currencies[i].available > minAvailable &&
            marginPercent < maxMarginPercent)
        {
            printInfoCurr(currencies[i]);
            found = true;
        }
    }

    if (!found) {
        cout << "Няма валути, които да отговарят на зададените критерии.\n";
    }
}

void buyCurrency(Currency currencies[], const unsigned int count) {
    string iso;
    cout << "Въведете ISO код на валутата за покупка: " << endl;
    cin >> iso;

    int idx = findByISOCurrencyreturn(currencies, count, iso);

    if (idx == -1) {
        cout << "Обменното бюро не работи с подобна валута." << endl;
        return;
    }

    Currency& c = currencies[idx];

    if (!c.isTraded) {
        cout << "Валутата не се търгува." << endl;
        return;
    }

    double amount;
    cout << "Въведете сумата, която искате да закупите: " << endl;
    cin >> amount;

    int idxBGN = findByISOCurrencyreturn(currencies, count, "BGN");

    if (idxBGN == -1) {
        cout << "Грешка: няма BGN валута в системата." << endl;
        return;
    }

    Currency& bgn = currencies[idxBGN];

    double requiredBGN = amount * c.sellRate;

    if (amount > c.maxTransaction || amount > c.available || bgn.available < requiredBGN) {
        cout << "Не може да бъде изпълнено! ";
        cout << "Надвишавате лимита, наличността на валутата или наличността на BGN.\n";
        cout << "Искате ли да закупите по-малко количество? (1=Да / 0=Не): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Въведете ново количество: ";
            cin >> amount;

            requiredBGN = amount * c.sellRate;

            if (amount > c.available) {
                cout << "Новото количество (" << amount
                    << ") все още е по-голямо от наличността на валутата ("
                    << c.available << ")." << endl;
                return;
            }

            if (amount > c.maxTransaction) {
                cout << "Новото количество (" << amount
                    << ") все още надвишава максималната стойност за транзакция ("
                    << c.maxTransaction << ")." << endl;
                return;
            }

            if (requiredBGN > bgn.available) {
                cout << "За покупката са нужни " << requiredBGN
                    << " BGN, но обменното бюро има само "
                    << bgn.available << " BGN." << endl;
                return;
            }

        }
        else {
            return;
        }
    }

    c.available -= amount;

    bgn.available -= requiredBGN;

    cout << "Успешна покупка!" << endl;
}

void sellCurrency(Currency currencies[], const unsigned int count) {
    string iso;
    cout << "Въведете ISO код на валутата за продажба: " << endl;
    cin >> iso;

    int idx = findByISOCurrencyreturn(currencies, count, iso);

    if (idx == -1) {
        cout << "Обменното бюро не работи с подобна валута." << endl;
        return;
    }

    Currency& c = currencies[idx];

    if (!c.isTraded) {
        cout << "Валутата не се търгува." << endl;
        return;
    }

    double amount;
    cout << "Въведете сумата, която искате да продадете: " << endl;
    cin >> amount;

    if (amount > c.maxTransaction) {
        cout << "Сумата е над максималната за транзакция." << endl;
        return;
    }

    double neededBGN = amount * c.buyRate;
    int idxBGN = findByISOCurrencyreturn(currencies, count, "BGN");

    if (idxBGN == -1) {
        cout << "Грешка: няма BGN валута в системата.\n";
        return;
    }

    if (currencies[idxBGN].available < neededBGN) {
        cout << "Няма достатъчно наличност от BGN.\n";
        return;
    }

    currencies[idxBGN].available -= neededBGN;
    c.available += amount;

    cout << "Успешна продажба!" << endl;
}

int main()
{

    Currency currencies[MAX_CURRENCIES];
    unsigned int currencyCount = 0;

    system("CHCP 1251 > nul");

    loadFromFile(currencies, currencyCount);

    unsigned int funcNum;

    cout << "Въведи функция: " << endl;
    showMenu();

    cin >> funcNum;

    do {
        switch (funcNum)
        {
        case 1: addCurrencies(currencies, currencyCount); break;

        case 2: displayCurrencies(currencies, currencyCount); break;

        case 3:
        {
            searchAndshowMenu();

            int findFuncNum;
            string reqIso;
            cin >> findFuncNum;

            switch (findFuncNum)
            {

            case 1:
                findLowestAvailability(currencies, currencyCount);

                break;

            case 2:
                cout << "Въведете ISO код: ";
                cin >> reqIso;
                findByISO(currencies, currencyCount, reqIso);

                break;

            case 0:

                break;
            }

            break;
        }

        case 4: sortTheMainArray(currencies, currencyCount); break;

        case 5:
        {
            int f;
            cout << "1. Запис\n2. Зареждане\n";
            cin >> f;
            if (f == 1) saveToFile(currencies, currencyCount);
            else if (f == 2) loadFromFile(currencies, currencyCount);
            break;
        }


        case 6:
        {
            cout << "Вие достигнахте второто меню." << endl;
            secondFuncMenu();

            int secondFuncChoice;
            cin >> secondFuncChoice;

            switch (secondFuncChoice)
            {
            case 1: {
                showTradedSortedByName(currencies, currencyCount);

                break;
            }

            case 2: {
                double searchedAvailable, MarginPercent;

                cout << "Въведете минимална наличност: ";
                cin >> searchedAvailable;

                cout << "Въведете максимален марж (в проценти): ";
                cin >> MarginPercent;

                findByAvailabilityAndMargin(
                    currencies,
                    currencyCount,
                    searchedAvailable,
                    MarginPercent
                );
                break;
            }

            case 0:
                break;

            default:
                cout << "Невалидна функция!" << endl;
            }

            break;
        }


        case 7:
        {
            int hChoice;
            purchaseSaleMenu();
            cin >> hChoice;

            switch (hChoice) {
            case 1: 
                buyCurrency(currencies, currencyCount); 
                
                break;
            case 2: 
                sellCurrency(currencies, currencyCount); 
                
                break;
            case 0: 
                
                break;

            default: cout << "Невалидна функция!" << endl;
            }
            break;
        }

        case 0: cout << "Изход" << endl; break;

        default: cout << "Невалидна функция!" << endl;
        }

        showMenu();
        cin >> funcNum;

    } while (funcNum != 0);

    saveToFile(currencies, currencyCount);

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu 
// // Debug program: F5 or Debug > Start Debugging menu 
// // Tips for Getting Started: 
// // 1. Use the Solution Explorer window to add/manage files 
// // 2. Use the Team Explorer window to connect to source control 
// // 3. Use the Output window to see build output and other messages 
// // 4. Use the Error List window to view errors 
// // 5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project 
// // 6. In the future, to open this project again, go to File > Open > Project and select the .sln file