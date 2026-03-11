#include <iostream>
#include <string>
using namespace std;

// Функція для перевірки, чи символ є літерою від A до K
bool isLetterAtoK(char c) {
    return (c >= 'A' && c <= 'K');
}
// Стани автомата
    enum State { S0, S1, S2, S3, ERROR };

// Функція сканера, яка розпізнає ланцюжок
bool scanner(const string& word) {
    
    State currentState = S0;

    // Перевірка на порожній рядок
    if (word.empty()) {
        return false;
    }

    // Обробка кожного символу
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];

        switch (currentState) {
        case S0:
            // Початковий стан: очікуємо '_'
            if (c == '_') {
                currentState = S1;
            }
            else {
                currentState = ERROR;
            }
            break;

        case S1:
            // Прочитано '_': очікуємо '+' або '-'
            if (c == '+' || c == '-') {
                currentState = S2;
            }
            else {
                currentState = ERROR;
            }
            break;

        case S2:
            // Прочитано '_+' або '_-': очікуємо літеру A-K
            if (isLetterAtoK(c)) {
                currentState = S3;
            }
            else {
                currentState = ERROR;
            }
            break;

        case S3:
            // Прочитано '_+A' (або подібне): можемо читати ще літери A-K
            if (isLetterAtoK(c)) {
                currentState = S3; // залишаємось в S3
            }
            else {
                currentState = ERROR;
            }
            break;

        case ERROR:
            // Помилка - виходимо
            return false;
        }

        // Якщо потрапили в стан ERROR, виходимо
        if (currentState == ERROR) {
            return false;
        }
    }

    // Перевірка фінального стану
    // Приймаємо тільки якщо закінчили в стані S3
    return (currentState == S3);
}

int main() {
    string input;

    cout << "=== Сканер для розпізнавання ланцюжків мови L(V) ===" << endl;
    cout << "Алфавіт: '_', 'A'-'K', '+', '-'" << endl;
    cout << "Формат: _[+|-][A-K]+" << endl;
    cout << "Приклади: _+ABC, _-DEFGH" << endl;
    cout << "=====================================================" << endl << endl;

    while (true) {
        cout << "Введіть ланцюжок (або 'exit' для виходу): ";
        getline(cin, input);

        // Вихід з програми
        if (input == "exit" || input == "EXIT") {
            cout << "Завершення програми." << endl;
            break;
        }

        // Розпізнавання ланцюжка
        bool result = scanner(input);

        if (result) {
            cout << "✓ Ланцюжок \"" << input << "\" НАЛЕЖИТЬ мові L(V)" << endl;
        }
        else {
            cout << "✗ Ланцюжок \"" << input << "\" НЕ НАЛЕЖИТЬ мові L(V)" << endl;
        }
        cout << endl;
    }

    // Тестові приклади
    cout << "\n=== Автоматичне тестування ===" << endl;
    string testCases[] = {
        "_+ABC",    // ∈ L(V)
        "_-ABC",    // ∈ L(V)
        "_+A",      // ∈ L(V)
        "_-ABCDEFGHIJK",  // ∈ L(V)
        "+ABC",     // ∉ L(V)
        "_ABC",     // ∉ L(V)
        "ABC",      // ∉ L(V)
        "_+",       // ∉ L(V)
        "_-ABC1",   // ∉ L(V)
        "",         // ∉ L(V)
        "_+ABCL"    // ∉ L(V) (L не входить в алфавіт)
    };

    for (const string& test : testCases) {
        bool result = scanner(test);
        cout << (result ? "✓ " : "✗ ") << "\"" << test << "\" -> "
            << (result ? "НАЛЕЖИТЬ L(V)" : "НЕ НАЛЕЖИТЬ L(V)") << endl;
    }

    return 0;
}