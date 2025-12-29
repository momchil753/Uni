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
    cout << "=== ÎÁÌÅÍÍÎ ÌÅÍÞ 1 ===" << endl;
    cout << "1. Äîáàâÿíå íà âàëóòè" << endl;
    cout << "2. Èçâåæäàíå íà âñè÷êè âàëóòè" << endl;
    cout << "3. Òúðñåíå" << endl;
    cout << "4. Ïîäðåæäàíå" << endl;
    cout << "5. Óïðàâëåíèå íà ôàéë" << endl;
    cout << "6. Äîïúëíèòåëíî ìåíþ 2" << endl;
    cout << "7. Ïîêóïêî-ïðîäàæáà" << endl;
    cout << "0. Èçõîä" << endl;
    cout << "Èçáîð: " << endl;
}

void searchAndshowMenu() {
    cout << "=== Ìåíþ çà òúðñåíå è èçâåæäàíå ===" << endl;
    cout << "1. Òúðñåíå ïî íàé-íèñêà íàëè÷íîñò" << endl;
    cout << "2. Òúðñåíå ïî ISO êîä" << endl;
    cout << "0. Íàçàä" << endl;
}

void secondFuncMenu() {
    cout << "=== ÎÁÌÅÍÍÎ ÌÅÍÞ 2 ===" << endl;
    cout << "1. Èçâåæäàíå íà âàëóòèòå, êîèòî ñå òúðãóâàò" << endl;
    cout << "2. Òúðñåíå íà âàëóòè ïî âúâåäåíà îò êëàâèàòóðàòà ñòîéíîñò" << endl;
    cout << "0. Íàçàä" << endl;;
}

void purchaseSaleMenu() {
    cout << "=== ÌÅÍÞ ÇÀ ÏÎÊÓÏÊÎ/ÏÐÎÄÀÆÁÀ ===" << endl;
    cout << "1. Ïîêóïêà íà âàëóòà" << endl;;
    cout << "2. Ïðîäàæáà íà âàëóòà" << endl;
    cout << "0. Íàçàä" << endl;
}

void printInfoCurr(const Currency& c)
{
    cout << "Èìå: " << c.name << " ---- " << endl
        << "ISO êîä: " << c.isoCode << " ---- " << endl
        << "Êóðñ ïðîäàâà: " << c.sellRate << " ---- "
        << "Êóðñ êóïóâà: " << c.buyRate << " ---- " << endl
        << "Íàëè÷íîñò: " << c.available << " ---- " << endl
        << "Ìàêñ. ñóìà çà òðàíçàêöèÿ: " << c.maxTransaction << " ---- " << endl
        << "Òúðãóâà ëè ñå: " << (c.isTraded ? "Äà" : "Íå") << "\n" << endl;

}

void addCurrencies(Currency currencies[], unsigned int& currencyCount) {

    int newCurrencies;

    cout << "Êîëêî âàëóòè èñêàòå äà äîáàâèòå?" << endl;
    cin >> newCurrencies;

    if (currencyCount + newCurrencies > MAX_CURRENCIES) {
        cout << "Íàäâèøàâàòå ìàêñèìàëíèÿ áðîé îò 50 âàëóòè!" << endl;
        return;
    }

    for (int i = 0; i < newCurrencies; i++) {
        Currency c;
        int traded;

        cout << "Âàëóòà #" << currencyCount + 1 << ":" << endl;
        cout << "Íàèìåíîâàíèå: "; cin >> c.name;
        cout << "Êîä ïî ISO: "; cin >> c.isoCode;
        cout << "Êóðñ ïðîäàâà: "; cin >> c.sellRate;
        cout << "Êóðñ êóïóâà: "; cin >> c.buyRate;
        cout << "Íàëè÷íîñò: "; cin >> c.available;
        cout << "Ìàêñ. ñóìà çà òðàíçàêöèÿ: "; cin >> c.maxTransaction;
        cout << "Òúðãóâà ëè ñå (1=Äà / 0=Íå): "; cin >> traded;

        if (traded == 1) {
            c.isTraded = true;
        }
        else {
            c.isTraded = false;
        }

        currencies[currencyCount] = c;
        currencyCount++;

        cout << "Âàëóòàòà áåøå äîáàâåíà!\n" << endl;
    }
}

void displayCurrencies(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Íÿìà äîáàâåíè âàëóòè." << endl;
        return;
    }

    cout << "=== Ñïèñúê ñ âàëóòè ===" << endl;

    for (int i = 0; i < count; i++) {
        printInfoCurr(currencies[i]);
    }

    cout << "=== Êðàé íà ñïèñúêà ñ âàëóòè ===" << endl;
}

void findLowestAvailability(const Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Íÿìà äîáàâåíè âàëóòè.\n";
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
        cout << "Íÿìà äîáàâåíè âàëóòè.\n";
        return;
    }

    int res = findByISOCurrencyreturn(currencies, count, reqIsoCode);

    if (res != -1)
    {
        printInfoCurr(currencies[res]);
        return;
    }

    cout << "Íÿìà âàëóòà ñ òîçè ISO êîä.\n";
}

void sortTheMainArray(Currency currencies[], const unsigned int count) {

    if (count == 0) {
        cout << "Íÿìà äîáàâåíè âàëóòè.\n";
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

    cout << "Âàëóòèòå áÿõà ïîäðåäåíè â íàìàëÿâàù ðåä ñïîðåä ìàðæà.\n" << endl;
}

void saveToFile(const Currency currencies[], const unsigned int count)
{
    ofstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Ãðåøêà ïðè îòâàðÿíå íà ôàéëà çà çàïèñ!\n";
        return;
    }

    file.write((char*)&count, sizeof(count));
    file.write((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Äàííèòå ñà çàïèñàíè âúâ ôàéëà.\n";
}

void loadFromFile(Currency currencies[], unsigned int& count)
{
    ifstream file(FILE_NAME, ios::binary);

    if (!file) {
        cout << "Ôàéëúò íå ñúùåñòâóâà. Ñòàðòèðàíå ñ ïðàçåí ñïèñúê.\n";
        count = 0;
        return;
    }

    file.read((char*)&count, sizeof(count));
    file.read((char*)currencies, sizeof(Currency) * count);

    file.close();
    cout << "Äàííèòå ñà çàðåäåíè îò ôàéëà.\n";
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
        cout << "Íÿìà íàëè÷íè âàëóòè!" << endl;
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
        cout << "Íÿìà âàëóòè, êîèòî äà îòãîâàðÿò íà çàäàäåíèòå êðèòåðèè.\n";
    }
}

void buyCurrency(Currency currencies[], const unsigned int count) {
    string iso;
    cout << "Âúâåäåòå ISO êîä íà âàëóòàòà çà ïîêóïêà: " << endl;
    cin >> iso;

    int idx = findByISOCurrencyreturn(currencies, count, iso);

    if (idx == -1) {
        cout << "Îáìåííîòî áþðî íå ðàáîòè ñ ïîäîáíà âàëóòà." << endl;
        return;
    }

    Currency& c = currencies[idx];

    if (!c.isTraded) {
        cout << "Âàëóòàòà íå ñå òúðãóâà." << endl;
        return;
    }

    double amount;
    cout << "Âúâåäåòå ñóìàòà, êîÿòî èñêàòå äà çàêóïèòå: " << endl;
    cin >> amount;

    int idxBGN = findByISOCurrencyreturn(currencies, count, "BGN");

    if (idxBGN == -1) {
        cout << "Ãðåøêà: íÿìà BGN âàëóòà â ñèñòåìàòà." << endl;
        return;
    }

    Currency& bgn = currencies[idxBGN];

    double requiredBGN = amount * c.sellRate;

    if (amount > c.maxTransaction || amount > c.available || bgn.available < requiredBGN) {
        cout << "Íå ìîæå äà áúäå èçïúëíåíî! ";
        cout << "Íàäâèøàâàòå ëèìèòà, íàëè÷íîñòòà íà âàëóòàòà èëè íàëè÷íîñòòà íà BGN.\n";
        cout << "Èñêàòå ëè äà çàêóïèòå ïî-ìàëêî êîëè÷åñòâî? (1=Äà / 0=Íå): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Âúâåäåòå íîâî êîëè÷åñòâî: ";
            cin >> amount;

            requiredBGN = amount * c.sellRate;

            if (amount > c.available) {
                cout << "Íîâîòî êîëè÷åñòâî (" << amount
                    << ") âñå îùå å ïî-ãîëÿìî îò íàëè÷íîñòòà íà âàëóòàòà ("
                    << c.available << ")." << endl;
                return;
            }

            if (amount > c.maxTransaction) {
                cout << "Íîâîòî êîëè÷åñòâî (" << amount
                    << ") âñå îùå íàäâèøàâà ìàêñèìàëíàòà ñòîéíîñò çà òðàíçàêöèÿ ("
                    << c.maxTransaction << ")." << endl;
                return;
            }

            if (requiredBGN > bgn.available) {
                cout << "Çà ïîêóïêàòà ñà íóæíè " << requiredBGN
                    << " BGN, íî îáìåííîòî áþðî èìà ñàìî "
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

    cout << "Óñïåøíà ïîêóïêà!" << endl;
}

void sellCurrency(Currency currencies[], const unsigned int count) {
    string iso;
    cout << "Âúâåäåòå ISO êîä íà âàëóòàòà çà ïðîäàæáà: " << endl;
    cin >> iso;

    int idx = findByISOCurrencyreturn(currencies, count, iso);

    if (idx == -1) {
        cout << "Îáìåííîòî áþðî íå ðàáîòè ñ ïîäîáíà âàëóòà." << endl;
        return;
    }

    Currency& c = currencies[idx];

    if (!c.isTraded) {
        cout << "Âàëóòàòà íå ñå òúðãóâà." << endl;
        return;
    }

    double amount;
    cout << "Âúâåäåòå ñóìàòà, êîÿòî èñêàòå äà ïðîäàäåòå: " << endl;
    cin >> amount;

    if (amount > c.maxTransaction) {
        cout << "Ñóìàòà å íàä ìàêñèìàëíàòà çà òðàíçàêöèÿ." << endl;
        return;
    }

    double neededBGN = amount * c.buyRate;
    int idxBGN = findByISOCurrencyreturn(currencies, count, "BGN");

    if (idxBGN == -1) {
        cout << "Ãðåøêà: íÿìà BGN âàëóòà â ñèñòåìàòà.\n";
        return;
    }

    if (currencies[idxBGN].available < neededBGN) {
        cout << "Íÿìà äîñòàòú÷íî íàëè÷íîñò îò BGN.\n";
        return;
    }

    currencies[idxBGN].available -= neededBGN;
    c.available += amount;

    cout << "Óñïåøíà ïðîäàæáà!" << endl;
}

int main()
{

    Currency currencies[MAX_CURRENCIES];
    unsigned int currencyCount = 0;

    system("CHCP 1251 > nul");

    loadFromFile(currencies, currencyCount);

    unsigned int funcNum;

    cout << "Âúâåäè ôóíêöèÿ: " << endl;
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
                cout << "Âúâåäåòå ISO êîä: ";
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
            cout << "1. Çàïèñ\n2. Çàðåæäàíå\n";
            cin >> f;
            if (f == 1) saveToFile(currencies, currencyCount);
            else if (f == 2) loadFromFile(currencies, currencyCount);
            break;
        }


        case 6:
        {
            cout << "Âèå äîñòèãíàõòå âòîðîòî ìåíþ." << endl;
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

                cout << "Âúâåäåòå ìèíèìàëíà íàëè÷íîñò: ";
                cin >> searchedAvailable;

                cout << "Âúâåäåòå ìàêñèìàëåí ìàðæ (â ïðîöåíòè): ";
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
                cout << "Íåâàëèäíà ôóíêöèÿ!" << endl;
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

            default: cout << "Íåâàëèäíà ôóíêöèÿ!" << endl;
            }
            break;
        }

        case 0: cout << "Èçõîä" << endl; break;

        default: cout << "Íåâàëèäíà ôóíêöèÿ!" << endl;
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
