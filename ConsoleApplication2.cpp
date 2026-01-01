#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_CURRENCIES = 50;
const char FILE_NAME[] = "CurrenciesArr.dat";

struct Currency {
    char name[30];
    string isoCode;
    double sellRate;
    double buyRate;
    double available;
    double maxTransaction;
    bool isTraded;
};

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int readIntNonNegative() {
    int x;
    while (!(cin >> x) || x < 0) {
        clearInput();
        cout << "Грешка! Въведете цяло число >= 0: ";
    }
    return x;
}

int readIntPositive() {
    int x;
    while (!(cin >> x) || x <= 0) {
        clearInput();
        cout << "Грешка! Въведете цяло положително число: ";
    }
    return x;
}

double readDoubleNonNegative() {
    double x;
    while (!(cin >> x) || x < 0) {
        clearInput();
        cout << "Грешка! Въведете число >= 0: ";
    }
    return x;
}

double readDoublePositive() {
    double x;
    while (!(cin >> x) || x <= 0) {
        clearInput();
        cout << "Грешка! Въведете положително число: ";
    }
    return x;
}

int readZeroOrOne() {
    int x;
    while (!(cin >> x) || (x != 0 && x != 1)) {
        clearInput();
        cout << "Грешка! Въведете 1 (Да) или 0 (Не): ";
    }
    return x;
}

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

int findBGNIndex(const Currency currencies[], unsigned int count) {
    if (count == 0) {
        return -1;
    }

    for (unsigned int i = 0; i < count; i++) {
        if (currencies[i].name[0] == 'B' &&
            currencies[i].name[1] == 'G' &&
            currencies[i].name[2] == 'N' &&
            currencies[i].name[3] == '\0') {

            return i;
        }
    }

    return -1;
}

void printLine() {
    cout << setfill('-') << setw(16) << "+" << setw(11) << "+" << setw(15) << "+"
        << setw(20) << "+" << setw(15) << "+" << setw(13) << "+" << setw(10) << "+" << setfill(' ') << endl;
}

void printHeader() {
    cout << "=== Списък с валути ===" << endl;
    printLine();
    cout << "| " << left << setw(14) << "Име"
        << "| " << setw(9) << "ISO"
        << "| " << setw(13) << "Курс продава"
        << "| " << setw(18) << "Курс купува"
        << "| " << setw(13) << "Наличност"
        << "| " << setw(11) << "Макс. сума"
        << "| " << setw(8) << "Търгува" << "|" << endl;
    printLine();
}

void printFooter() {
    printLine();
    cout << "=== Край на списъка с валути ===" << endl;
}

int findByISOCurrencyreturn(const Currency currencies[], const unsigned int count, const string& iso) {
    for (int i = 0; i < count; i++) {
        if (currencies[i].isoCode == iso) return i;
    }
    return -1;
}

void printInfoCurr(const Currency& c) {
    cout << "| " << left << setw(14) << c.name
        << "| " << setw(9) << c.isoCode
        << "| " << fixed << setprecision(4) << setw(13) << c.sellRate
        << "| " << setw(18) << c.buyRate
        << "| " << fixed << setprecision(2) << setw(13) << c.available
        << "| " << setw(11) << c.maxTransaction
        << "| " << setw(8) << (c.isTraded ? "Да" : "He") << "|" << endl;
}

void addCurrencies(Currency currencies[], unsigned int& currencyCount) {

    int newCurrencies;

    cout << "Колко валути искате да добавите?\n";
    while (true) {
        newCurrencies = readIntPositive();

        if (currencyCount + newCurrencies <= MAX_CURRENCIES) break;

        cout << "Надвишавате максималния брой от 50 валути! Въведете ново число: ";
    }

    for (int i = 0; i < newCurrencies; i++) {
        Currency c;
        int traded;

        cout << "Валута #" << currencyCount + 1 << ":\n";
        cout << "Наименование: "; cin >> c.name;
        cout << "Код по ISO: "; cin >> c.isoCode;

        if (findByISOCurrencyreturn(currencies, currencyCount, c.isoCode) != -1) {
            cout << "Валута с този ISO код вече съществува!\n";
            i--;
            continue;
        }

        cout << "Курс продава: ";
        c.sellRate = readDoublePositive();

        cout << "Курс купува: ";
        c.buyRate = readDoublePositive();

        cout << "Наличност: ";
        c.available = readDoubleNonNegative();

        cout << "Макс. сума за транзакция: ";
        c.maxTransaction = readDoublePositive();

        cout << "Търгува ли се (1=Да / 0=Не): ";
        traded = readZeroOrOne();
        c.isTraded = (traded == 1);

        currencies[currencyCount++] = c;
        cout << "Валутата беше добавена!\n";
    }
}

void displayCurrencies(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути." << endl;
        return;
    }


    printHeader();

    for (int i = 0; i < count; i++) {
        printInfoCurr(currencies[i]);
    }

    printFooter();

}

void findLowestAvailability(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути." << endl;
        return;
    }

    int idx = 0;

    for (int i = 1; i < count; i++) {
        if (currencies[i].available < currencies[idx].available)
            idx = i;
    }

    printHeader();
    printInfoCurr(currencies[idx]);
}

void findByISO(const Currency currencies[], const unsigned int count, const string& reqIsoCode) {

    if (count == 0) {
        cout << "Няма добавени валути с този ISO код." << endl;
        return;
    }

    int res = findByISOCurrencyreturn(currencies, count, reqIsoCode);

    if (res != -1)
    {
        printHeader();
        printInfoCurr(currencies[res]);
        printFooter();
        return;
    }

    cout << "Няма валута с този ISO код." << endl;
}

void sortTheMainArray(Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Няма добавени валути." << endl;
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

    cout << "Валутите бяха подредени в намаляващ ред според маржа." << endl;
}

void saveToFile(const Currency currencies[], const unsigned int count)
{
    ofstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Грешка при отваряне на файла за запис!" << endl;
        return;
    }

    file.write((char*)&count, sizeof(count));
    file.write((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Данните са записани във файла." << endl;
}

void loadFromFile(Currency currencies[], unsigned int& count)
{
    ifstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Файлът не съществува." << endl;
        count = 0;
        return;
    }

    file.read((char*)&count, sizeof(count));

    if (count > MAX_CURRENCIES) {
        cout << "Няма достатъчно място в основния масив!" << endl;
        count = 0;
        file.close();
        return;
    }

    file.read((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Данните са заредени от файла." << endl;
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
        cout << "Няма валути, които да отговарят на зададените критерии." << endl;
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

    if ((!c.isTraded) || (c.name == "BGN")) {
        cout << "Валутата не се търгува." << endl;
        return;
    }

    double amount;
    cout << "Въведете сумата, която искате да закупите: " << endl;
    amount = readDoublePositive();

    int idxBGN = findBGNIndex(currencies, count);

    if (idxBGN == -1) {
        cout << "Грешка: няма BGN валута в системата." << endl;
        return;
    }

    Currency& bgn = currencies[idxBGN];

    double requiredBGN = amount * c.buyRate;

    while (amount > c.maxTransaction ||
        amount > c.available ||
        bgn.available < requiredBGN) {

        cout << "Не може да бъде изпълнено!\n";
        cout << "Причина: надвишен лимит, недостатъчна наличност на валутата или BGN.\n";
        cout << "Искате ли да въведете по-малко количество? (1=Да / 0=Не): ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            return;
        }

        cout << "Въведете ново количество: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Количеството трябва да е положително число.\n";
        }

        requiredBGN = amount * c.sellRate;

        if (amount > c.available) {
            cout << "Налично количество: " << c.available << endl;
        }

        if (amount > c.maxTransaction) {
            cout << "Максимално позволено количество: "
                << c.maxTransaction << endl;
        }

        if (requiredBGN > bgn.available) {
            cout << "Нужни BGN: " << requiredBGN
                << ", налични BGN: " << bgn.available << endl;
        }
    }


    c.available += amount;

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

    if ((!c.isTraded) || (c.name == "BGN")) {
        cout << "Валутата не се търгува." << endl;
        return;
    }

    double amount;
    cout << "Въведете сумата, която искате да продадете: " << endl;
    amount = readDoublePositive();

    if (amount > c.maxTransaction) {
        cout << "Сумата е над максималната за транзакция." << endl;
        return;
    }

    double neededBGN = amount * c.sellRate;
    int idxBGN = findBGNIndex(currencies, count);

    if (idxBGN == -1) {
        cout << "Грешка: няма BGN валута в системата." << endl;
        return;
    }

    if (c.available < amount) {
        cout << "Няма достатъчно наличност от: "<< c.name << endl;
        return;
    }

    currencies[idxBGN].available += neededBGN;
    c.available -= amount;

    cout << "Успешна продажба!" << endl;
}

int main()
{

    Currency currencies[MAX_CURRENCIES];
    unsigned int currencyCount = 0;

    system("CHCP 1251 > nul");

    loadFromFile(currencies, currencyCount);

    unsigned int funcNum;

 
    do {
        showMenu();
        cout << "Въведете вашия избор: " << endl;

        cin >> funcNum;

        if (!cin) {
            clearInput();
            cin.ignore(10000, '\n');
            cout << "Невалидна функция! Въведете нова стойност за избор.\n" << endl;
            continue;
        }

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

            if (!cin) {
                clearInput();
                continue;
            }


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

            default: cout << "Невалидна функция! Въведете нова стойност за избор.\n" << endl;
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

            cin >> secondFuncChoice;
            if (!cin) {
                clearInput();
                continue;
            }


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
                cout << "Невалидна функция! Въведете нова стойност за избор.\n" << endl;
            }

            break;
        }


        case 7:
        {
            int hChoice;
            purchaseSaleMenu();
            cin >> hChoice;

            cin >> hChoice;
            if (!cin) {
                clearInput();
                continue;
            }


            switch (hChoice) {
            case 1: 
                buyCurrency(currencies, currencyCount); 
                
                break;
            case 2: 
                sellCurrency(currencies, currencyCount); 
                
                break;
            case 0: 
                
                break;

            default: cout << "Невалидна функция! Въведете нова стойност за избор.\n" << endl;
            }
            break;
        }

        case 0: cout << "Изход! Излизане от пограмата." << endl; break;

        default: cout << "Невалидна функция! Въведете нова стойност за избор.\n" << endl;
        }

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
