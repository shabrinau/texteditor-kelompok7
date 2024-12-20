#ifndef TUBESSTD_H_INCLUDED
#define TUBESSTD_H_INCLUDED
#include <iostream>
#include <string> // buat std::string
#include <stack>
#include <utility> // required untuk std::pair di stack
using namespace std;

// tipe data alias untuk string
typedef std::string infotype;
typedef struct ElmList *address;

// struktur untuk elemen list atau node
struct ElmList {
    infotype info;
    address next, prev;
};

// struktur untuk dll
struct List {
    address first, last;
};

void createList(List &L);
address createElm(const infotype &text);
void deallocate(address &P);
void insertFirst(List &L, infotype text);
void insertAt(List &L, infotype &text, int pos);
void deleteAt(List &L, int pos);
void display(const List &L);

// struktur untuk stack yang berbasis list
struct Stack {
    List aksi;
};

void createStack(Stack &S);
void push(Stack &s, infotype text);
infotype pop(Stack &S);
bool isEmpty(const Stack &S);

// struktur utama unntuk text editor
struct TextEditor {
    List content;
    std::stack<std::pair<std::string, int>> undoStack; // ngetrack aksi undo
    std::stack<std::pair<std::string, int>> redoStack; // ngetrack aksi redo
};

void initializeEditor(TextEditor &editor);
void insertText(TextEditor &editor, const string &text, int pos);
void deleteText(TextEditor &editor, int pos);
void displayText(const TextEditor &editor);
void searchWord(const TextEditor &editor, const string &word);
void replaceWord(TextEditor &editor, const string &oldWord, const string &newWord);
void navigateToLine(const TextEditor &editor, int line);
void undo(TextEditor &editor);
void redo(TextEditor &editor);

#endif // TUBESSTD_H_INCLUDED
