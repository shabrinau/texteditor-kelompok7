#include "tubesstd.h"

// fungsi untuk inisialisasi list kosong
void createList(List &L){
    L.first = nullptr;
    L.last = nullptr;
}

// fungsi untuk membuat elemen baru di dalam list
address createElm(const infotype &text){
    address P = new ElmList;
    P->info = text; // isi elemen dengan teks
    P->next = nullptr; // belum ada elemen berikutnya
    P->prev = nullptr; // belum ada elemen sebelumnya
    return P;
}

// fungsi untuk menghapus elemen list dari memori
void deallocate(address &P){
    delete P; // hapus elemen dari memori
    P = nullptr; // null-kan ke pointer
}

// fungsi untuk menambahkan elemen di awal list
void insertFirst(List &L, infotype text){
    address P = createElm(text);
    if (L.first == nullptr) { // jika list kosong
        L.first = L.last = P; // elemen jadi elemen pertama & terakhir
    } else { // jika list sudah ada isinya
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
    cout << "Inserted at first: " << text << endl;
}
// fungsi untuk menambahkan elemen ke posisi tertentu
void insertAt(List &L, infotype &text, int pos) {
    if (pos <= 0) { // jika posisinya awal
        insertFirst(L, text);
        return;
    }
    address P = L.first;
    for (int i=0; i<pos-1 && P != nullptr; i++) {
        P = P->next; // navigasi ke elemen yang dituju
    }
    if (P == nullptr){ // jika posisi tidak valid
        return;
    }
    address Q = createElm(text); // buat elemen baru
    Q->next = P->next;
    Q->prev = P;
    if (P->next != nullptr){
        P->next->prev = Q;
    } else {
        L.last = Q; // update elemen terakhir
    }
    P->next = Q;
}

//fungsi untuk menghapus elemen di posisi tertentu
void deleteAt(List &L, int pos) {
    if (L.first == nullptr){ // jika list kosong
        return;
    }
    address P = L.first;
    for (int i=0; i<pos && P != nullptr; i++){
        P = P->next; // navigasi ke elemen yang dituju
    }
    if (P == nullptr){ // jika posisi tidak valid
        return;
    }
    if (P->prev != nullptr){ // jika bukan elemen pertama
        P->prev->next = P->next;
    } else {
        L.first = P->next; // update elemen pertama
    }
    if (P->next != nullptr){ // jika bukan elemen terakhir
        P->next->prev = P->prev;
    } else {
        L.last = P->prev;// update elemen terakhir
    }
    deallocate(P);
}

// fungsi untuk menampilkan isi list
void display(const List &L){
    if (L.first == nullptr){ // jika list kosong
        cout << "List is empty." << endl;
        return;
    }
    address P = L.first;
    int line = 1;
    while (P != nullptr){
        cout << line << ". " << P->info << endl; // tampilkan tiap elemen
        P = P->next;
        line++;
    }
}

// fungsi untuk inisialisasi stack kosong
void createStack(Stack &S){
    createList(S.aksi); // stack pake list kosong
}

// fungsi untuk menambahkan elemen ke stack
void push(Stack &S, infotype text){
    insertFirst(S.aksi, text); // tambah elemen di awal
}

// fungsi untuk mengeluarkan elemen dari stack
infotype pop(Stack &S){
    if (isEmpty(S)){ // jika list kosong
        return "";
    }
    infotype text = S.aksi.first->info;
    deleteAt(S.aksi, 1); // hapus elemen pertama
    return text;
}

//fungsi untuk mengecek apakah stack kosong
bool isEmpty(const Stack &S){
    return S.aksi.first == nullptr;
}

// inisialisasi editor kosong
void initializeEditor(TextEditor &editor){
    createList(editor.content); // list kosong
    while (!editor.undoStack.empty()){
        editor.undoStack.pop(); // kosongkan undo stack
    }
    while (!editor.redoStack.empty()){
        editor.redoStack.pop(); // kosongkan redo stack
    }
}

// tambah teks di posisi tertentu
void insertText(TextEditor &editor, const string &text, int pos){
    insertAt(editor.content, const_cast<string&>(text), pos);
    editor.undoStack.push({"insert", pos}); // catat aksi untuk undo
    while (!editor.redoStack.empty()){
        editor.redoStack.pop(); // kosongkan redo stack
    }
}

// fungsi untuk menghapus teks di posisi tertentu
void deleteText(TextEditor &editor, int pos){
    address P = editor.content.first;
    int count = 1;
    while (P != nullptr && count < pos){
        P = P->next; // navigasi ke elemen yang dituju
        count++;
    }
    if (P == nullptr){ // jika posisi tidak valid
        return;
    }
    string deleteText = P->info; // simpan teks yang dihapus
    deleteAt(editor.content, pos); // hapus elemen
    editor.undoStack.push({"delete", pos}); // catat aksi untuk undo
    editor.redoStack.push({deleteText, pos}); // catat teks untuk redo
}

// fungsi untuk menampilkan isi editor
void displayText(const TextEditor &editor){
    display(editor.content); // memanggil fungsi display untuk list
}

// fungsi untuk mencari kata dalam teks
void searchWord(const TextEditor &editor, const string &word){
    address P = editor.content.first;
    int line = 1;
    bool found = false; // untuk mengecek apakah kata yang dicari ditemukan
    while (P != nullptr){
        if (P->info.find(word) != string::npos){ // cek apakah kata tsb ada di baris ini
            cout << "Found word" << " at line " <<  line << ": " << P->info << endl;
            found = true;
        }
        P = P->next;
        line++;
    }
    if (!found){ // jika kata yang dicari tidak ditemukan
        cout << "Word '" << word << "' not found in the text." << endl;
    }
}

// fungsi untuk mengganti kata dalam teks
void replaceWord(TextEditor &editor, const string &oldWord, const string &newWord){
    address P = editor.content.first;
    while (P != nullptr){
        size_t pos = P->info.find(oldWord); // cari posisi kata yang akan diganti
        while (pos != string::npos){
            P->info.replace(pos, oldWord.length(), newWord); // ganti kata
            pos = P->info.find(oldWord, pos + newWord.length()); // cari kata berikutnya
        }
        P = P->next;
    }
}

//fungsi untuk menavigasi ke baris tertentu
void navigateToLine(const TextEditor &editor, int line){
    address P = editor.content.first;
    int count = 1;
    while (P != nullptr && count < line){
        P = P->next; // navigasi ke baris yang dituju
        count++;
    }
    if (P != nullptr){ // jika baris ditemukan
        cout << "Line " << line << ": " << P->info << endl;
    } else { // jika baris tidak ada
        cout << "Line " << line << " does not exist." << endl;
    }
}

// fungsi untuk melakukan undo
void undo(TextEditor &editor){
    if (editor.undoStack.empty()){ // kalau tidak ada aksi untuk di-undo
        cout << "Nothing to undo.\n";
        return;
    }
    auto action = editor.undoStack.top(); // ambil aksi terakhir
    editor.undoStack.pop(); // hapus dari undo stack

    if (action.first == "insert"){ // jika aksi terakhir adalah insert
        deleteAt(editor.content, action.second); // hapus elemen yang di-insert
        editor.redoStack.push(action); // simpan ke redo stack
    } else if (action.first == "delete") { // jika aksi terakhir adalah delete
        insertAt(editor.content, const_cast<string&>(action.first), action.second); // tambah elemen kembali
        editor.redoStack.push(action); // simpan aksi ke redo stack
    }
}

// fungsi untuk melakukan redo
void redo(TextEditor &editor){ // kalau tidak ada aksi untuk di-redo
    if (editor.redoStack.empty()){
        cout << "Nothing to redo.\n";
        return;
    }
    auto action = editor.redoStack.top(); // ambil aksi terakhir di redo stack
    editor.redoStack.pop(); // hapus dari redo stack

    if (action.first == "insert"){ // jika aksi adalah insert
        insertAt(editor.content, const_cast<string&>(action.first), action.second); // tambah elemen kembali
        editor.undoStack.push(action); // simpan aksi ke undo stack
    } else if (action.first == "delete") { // jika aksi adalah delete
        deleteAt(editor.content, action.second); // hapus elemen
        editor.undoStack.push(action); // simpan aksi ke undo stack
    }
}
