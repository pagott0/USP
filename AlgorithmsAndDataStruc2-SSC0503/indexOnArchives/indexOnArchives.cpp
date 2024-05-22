#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Manga {
    string isbn;
    string title;
    string authors;
    int startYear;
    int endYear;
    string genre;
    string magazine;
    string publisher;
    int editionYear;
    int volumeCount;
    int acquiredVolumeCount;
    vector<int> acquiredVolumes;
};

vector<Manga> mangas;
unordered_map<string, int> primaryIndex; // Maps ISBN to vector index
unordered_map<string, vector<int>> secondaryIndex; // Maps title to vector indices

void loadMangas();
void saveMangas();
void loadIndexes();
void saveIndexes();

void createManga() {
    Manga manga;
    cout << "Enter ISBN: ";
    cin >> manga.isbn;
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, manga.title);
    cout << "Enter authors (separated by commas): ";
    getline(cin, manga.authors);
    cout << "Enter start year: ";
    cin >> manga.startYear;
    cin.ignore();
    cout << "Enter end year: ";
    cin >> manga.endYear;
    cin.ignore();
    cout << "Enter genre: ";
    getline(cin, manga.genre);
    cout << "Enter magazine: ";
    getline(cin, manga.magazine);
    cout << "Enter publisher: ";
    getline(cin, manga.publisher);
    cout << "Enter edition year: ";
    cin >> manga.editionYear;
    cout << "Enter volume count: ";
    cin >> manga.volumeCount;
    cout << "Enter acquired volume count: ";
    cin >> manga.acquiredVolumeCount;
    cin.ignore();
    cout << "Enter acquired volumes (separated by commas): ";
    string temp;
    getline(cin, temp);

    stringstream ss(temp);
    string volume;
    while (getline(ss, volume, ',')) {
        try {
            manga.acquiredVolumes.push_back(stoi(volume));
        } catch (invalid_argument&) {
            cerr << "Invalid volume number: " << volume << endl;
            continue;
        }
    }

    mangas.push_back(manga);
    primaryIndex[manga.isbn] = mangas.size() - 1;
    secondaryIndex[manga.title].push_back(mangas.size() - 1);
    saveMangas();
    saveIndexes();
}

void readMangas() {
    for (const auto& manga : mangas) {
        cout << "ISBN: " << manga.isbn << endl;
        cout << "Title: " << manga.title << endl;
        cout << "Authors: " << manga.authors << endl;
        cout << "Start year: " << manga.startYear << endl;
        cout << "End year: " << manga.endYear << endl;
        cout << "Genre: " << manga.genre << endl;
        cout << "Magazine: " << manga.magazine << endl;
        cout << "Publisher: " << manga.publisher << endl;
        cout << "Edition year: " << manga.editionYear << endl;
        cout << "Volume count: " << manga.volumeCount << endl;
        cout << "Acquired volume count: " << manga.acquiredVolumeCount << endl;
        cout << "Acquired volumes: ";
        for (int volume : manga.acquiredVolumes) {
            cout << volume << " ";
        }
        cout << endl;
        cout << endl;
    }
}

void updateManga() {
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;
    cin.ignore();

    if (primaryIndex.find(isbn) == primaryIndex.end()) {
        cout << "Manga not found." << endl;
        return;
    }

    int index = primaryIndex[isbn];
    Manga& manga = mangas[index];

    // Store old title to update secondary index
    string oldTitle = manga.title;

    cout << "Enter new title: ";
    getline(cin, manga.title);
    cout << "Enter new authors (separated by commas): ";
    getline(cin, manga.authors);
    cout << "Enter new start year: ";
    cin >> manga.startYear;
    cin.ignore();
    cout << "Enter new end year: ";
    cin >> manga.endYear;
    cin.ignore();
    cout << "Enter new genre: ";
    getline(cin, manga.genre);
    cout << "Enter new magazine: ";
    getline(cin, manga.magazine);
    cout << "Enter new publisher: ";
    getline(cin, manga.publisher);
    cout << "Enter new edition year: ";
    cin >> manga.editionYear;
    cout << "Enter new volume count: ";
    cin >> manga.volumeCount;
    cout << "Enter new acquired volume count: ";
    cin >> manga.acquiredVolumeCount;
    cin.ignore();
    cout << "Enter new acquired volumes (separated by commas): ";
    string temp;
    getline(cin, temp);
    manga.acquiredVolumes.clear();

    stringstream ss(temp);
    string volume;
    while (getline(ss, volume, ',')) {
        try {
            manga.acquiredVolumes.push_back(stoi(volume));
        } catch (invalid_argument&) {
            cerr << "Invalid volume number: " << volume << endl;
            continue;
        }
    }

    // Update the secondary index
    auto& indices = secondaryIndex[oldTitle];
    indices.erase(remove(indices.begin(), indices.end(), index), indices.end());
    if (indices.empty()) {
        secondaryIndex.erase(oldTitle);
    }
    secondaryIndex[manga.title].push_back(index);

    saveMangas();
    saveIndexes();
}

void deleteManga() {
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;
    cin.ignore();

    if (primaryIndex.find(isbn) == primaryIndex.end()) {
        cout << "Manga not found." << endl;
        return;
    }

    int index = primaryIndex[isbn];
    cout << "Are you sure you want to delete this manga? (y/n): ";
    char response;
    cin >> response;
    if (response == 'y') {
        string title = mangas[index].title;
        mangas.erase(mangas.begin() + index);
        primaryIndex.erase(isbn);
        auto& indices = secondaryIndex[title];
        indices.erase(remove(indices.begin(), indices.end(), index), indices.end());
        if (indices.empty()) {
            secondaryIndex.erase(title);
        }

        // Update all primary and secondary indexes
        for (int i = index; i < mangas.size(); ++i) {
            primaryIndex[mangas[i].isbn] = i;
            for (auto& pair : secondaryIndex) {
                replace(pair.second.begin(), pair.second.end(), i + 1, i);
            }
        }

        saveMangas();
        saveIndexes();
        cout << "Manga deleted." << endl;
    }
}

void loadMangas() {
    ifstream file("mangas.txt");
    if (file.is_open()) {
        Manga manga;
        while (file >> manga.isbn) {
            file.ignore();
            getline(file, manga.title);
            getline(file, manga.authors);
            file >> manga.startYear >> manga.endYear;
            file.ignore();
            getline(file, manga.genre);
            getline(file, manga.magazine);
            getline(file, manga.publisher);
            file >> manga.editionYear >> manga.volumeCount >> manga.acquiredVolumeCount;
            file.ignore();
            string temp;
            getline(file, temp);
            stringstream ss(temp);
            string volume;
            manga.acquiredVolumes.clear();
            while (getline(ss, volume, ',')) {
                manga.acquiredVolumes.push_back(stoi(volume));
            }
            mangas.push_back(manga);
        }
        file.close();
    }
}

void saveMangas() {
    ofstream file("mangas.txt");
    for (const auto& manga : mangas) {
        file << manga.isbn << endl;
        file << manga.title << endl;
        file << manga.authors << endl;
        file << manga.startYear << " " << manga.endYear << endl;
        file << manga.genre << endl;
        file << manga.magazine << endl;
        file << manga.publisher << endl;
        file << manga.editionYear << " " << manga.volumeCount << " " << manga.acquiredVolumeCount << endl;
        for (size_t i = 0; i < manga.acquiredVolumes.size(); ++i) {
            file << manga.acquiredVolumes[i];
            if (i < manga.acquiredVolumes.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }
    file.close();
}

void loadIndexes() {
    ifstream file("primaryIndex.txt");
    if (file.is_open()) {
        string isbn;
        int index;
        while (file >> isbn >> index) {
            primaryIndex[isbn] = index;
        }
        file.close();
    }

    file.open("secondaryIndex.txt");
    if (file.is_open()) {
        string title;
        int index;
        while (file >> title >> index) {
            secondaryIndex[title].push_back(index);
        }
        file.close();
    }
}

void saveIndexes() {
    ofstream file("primaryIndex.txt");
    for (const auto& pair : primaryIndex) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();

    file.open("secondaryIndex.txt");
    for (const auto& pair : secondaryIndex) {
        for (int index : pair.second) {
            file << pair.first << " " << index << endl;
        }
    }
    file.close();
}

int main() {
    loadMangas();
    loadIndexes();

    while (true) {
        cout << "1. Create manga" << endl;
        cout << "2. Read mangas" << endl;
        cout << "3. Update manga" << endl;
        cout << "4. Delete manga" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                createManga();
                break;
            case 2:
                readMangas();
                break;
            case 3:
                updateManga();
                break;
            case 4:
                deleteManga();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
