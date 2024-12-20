#include "tubesstd.h"

int main() {
    TextEditor editor;
    initializeEditor(editor); // inisialisasi text editor, kosongin list dan stack


    int pilih;
    string text, searchWordStr, replaceOld, replaceNew; // var untuk input user
    int posisi, line;

    do {
        // menu text editor
        cout << "\nText Editor Menu:\n";
        cout << "1. Insert Text\n";
        cout << "2. Delete Text\n";
        cout << "3. Display Text\n";
        cout << "4. Search Word\n";
        cout << "5. Replace Word\n";
        cout << "6. Navigate to Line\n";
        cout << "7. Undo\n";
        cout << "8. Redo\n";
        cout << "9. Exit\n";
        cout << "Masukkan pilihanmu: ";
        cin >> pilih; // bersihkan buffer input
        cin.ignore();

        switch (pilih) {
        case 1:
            cout << "Enter text to insert: ";
            getline(cin, text);
            cout << "Enter position to insert at: ";
            cin >> posisi;
            cin.ignore(); // bersihkan buffer input
            insertText(editor, text, posisi); // masukkan teks ke posisi tertentu
            break;

        case 2:
            cout << "Enter posistion to delete text from: ";
            cin >>posisi;
            cin.ignore(); // bersihkan buffer input
            deleteText(editor, posisi); // hapus teks di posisi tertentu
            break;

        case 3:
            cout << "\nCurrent Text:\n";
            displayText(editor);
            break;

        case 4:
            cout << "Enter word to search: ";
            cin >> searchWordStr;
            cin.ignore(); // bersihkan buffer input
            searchWord(editor, searchWordStr); // cari kata di text editor
            break;

        case 5:
            cout << "Enter word to replace: ";
            cin >> replaceOld;
            cin.ignore(); // bersihkan buffer input
            cout << "Enter new word: ";
            cin >> replaceNew;
            cin.ignore(); // bersihkan buffer input
            replaceWord(editor, replaceOld, replaceNew); // ganti kata
            break;

        case 6:
            cout << "Enter line number to navigate to: ";
            cin >> line;
            cin.ignore(); // bersihkan buffer input
            navigateToLine(editor, line); // navigasi ke baris
            break;

        case 7:
            undo(editor);
            cout << "Undo performed.\n";
            break;

        case 8:
            redo(editor);
            cout << "Redo performed.\n";
            break;

        case 9:
            cout << "Exiting Text Editor.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (pilih != 9);

    return 0;
}
