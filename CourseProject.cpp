#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>

using namespace std;

// Global variable
string g_file_path = "C:\\Users\\User\\Desktop\\data.bin";

// Formal function declaration
template<typename T>
T& ValidateInput(T&, string); // Function for validate user input

struct Classroom
{
public:
    // Empty base constructor of the struct
    Classroom() {}

    // Overloaded constructor of the struct
    Classroom(unsigned int _number, string _department, string _clroomType, float _area, unsigned int _seats)
    {
        number = _number;
        strcpy_s(department, _department.c_str());
        strcpy_s(clroom_type, _clroomType.c_str());
        area = _area;
        seats = _seats;
    }

    // SETTERS

    void setNumber(unsigned int _number)
    {
        number = _number;
    }

    void setDepartment(string _department)
    {
        strcpy_s(department, _department.c_str());
    }

    void setClroomType(string _clroomType)
    {
        // Acceptable classroom types
        const string types[] = { "Лекционная", "Лаборатория", "Профессиональный кабинет" };

        while (true)
        {
            for (unsigned int i = 0; i < size(types); i++)
            {
                if (_clroomType == types[i])
                {
                    strcpy_s(clroom_type, _clroomType.c_str());
                    return;
                }
            }

            cout << "(!) Тип аудитории должен быть одним из перечисленных:\n- Лекционная\n- Лаборатория\n- Профессиональный кабинет" << endl;
            cout << "(i) Введите тип аудитории заново." << endl;
            cout << "> ";

            getline(cin, _clroomType);
        }
    }

    void setArea(double _area)
    {
        while (true)
        {
            if (_area >= 30.0)
            {
                area = _area;
                return;
            }

            cout << "(!) Неверно указана площадь аудитории. Она не должна быть меньше 30квМ." << endl;
            cout << "(i) Введите площадь заново." << endl;

            _area = ValidateInput(_area, "> ");
        }   
    }

    void setSeats(unsigned int _seats)
    {
        while (true)
        {
            if (_seats > 24)
            {
                seats = _seats;
                return;
            }

            cout << "(!) Неверно указано количество мест. Их не должно быть меньше 25." << endl;
            cout << "(i) Введите количество мест заново." << endl;

            _seats = ValidateInput(_seats, "> ");
        }
    }

    // GETTERS

    unsigned int getNumber()
    {
        return number;
    }

    char* getDepartment()
    {
        return department;
    }

    char* getClroomType()
    {
        return clroom_type;
    }

    double getArea()
    {
        return area;
    }

    unsigned int getSeats()
    {
        return seats;
    }

private:
    unsigned int number;    // Number of classroom
    unsigned int seats;     // Seats inside a classroom
    double area;            // Area of classroom
    char department[50];    // The name of a department
    char clroom_type[50];   // Classroom type
};

// Formal functions declaration
void InitConfigFile();                  // Function for initialization of a configuration file
void EditConfigFile(string, string);    // Function for editing a configuration file
void ViewUIMainMenu();                  // Function of main menu of program
void ViewUIDataMenu();                  // Function of data edit menu
void ViewUIAddNewData();                // Function for displaying the menu of adding new data
void ViewUITable();                     // Function for displaying the names of a table columns
void CreateNewFile();                   // Function for creating a new file by user input
void ReadDataFromFile(string);          // Function for reading data from a binary file
void AddDataToFile(string);             // Function for adding data to a file
void DeleteDataFromFile(string);        // Function for deleting data from a file
void OutputDataAsTable(Classroom);      // Function for displaying data in the form of a table
void GetDataByDepAndType();             // Searches for matches by Department and Classroom type
void GetDataByMaxArea();                // Function for searching the biggest value of the classroom area
void GetDataBySeats();                  // Search for classrooms that contain the specified number of seats (or more)
void SetPathToFile(string&);            // Function for changing the file path
void SortByNumber(string);              // Function for sorting data in a binary file from min number to max number of classroom
bool IsFileGood(ifstream&);             // Function that checks the file for correctness
Classroom InputNewData();               // Function for entering a new data structure

int main()
{
    setlocale(LC_CTYPE, "rus");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle(L"Course Project by Diachenko Vladyslav");

    InitConfigFile();
    ViewUIMainMenu();

    return 0;
}

// Function of main menu of program
void ViewUIMainMenu()
{
    int menu_item;

    while (true)
    {
        system("cls");

        cout << "\tГлавное меню программы" << endl;
        cout << "1. Работа с данными" << endl;
        cout << "2. Аудитории по указанному отделению и типу" << endl;
        cout << "3. Аудитории с самыми большими площадями" << endl;
        cout << "4. Аудитории по указанному количеству мест" << endl;
        cout << "5. Указать путь к файлу" << endl;
        cout << "6. Выход из программы" << endl;
        cout << "\n(i) Введите пункт меню." << endl;

        menu_item = ValidateInput(menu_item, "> ");

        system("cls");

        switch (menu_item)
        {
        case 1:
            ViewUIDataMenu();
            break;
        case 2:
            GetDataByDepAndType();
            system("pause");
            break;
        case 3:
            GetDataByMaxArea();
            system("pause");
            break;
        case 4:
            GetDataBySeats();
            system("pause");
            break;
        case 5:
            SetPathToFile(g_file_path);
            system("pause");
            break;
        case 6:
            cout << "(i) Программа завершает работу..." << endl;
            system("pause");
            return;
        default:
            cout << "(!) Неправильно выбран пункт меню." << endl;
            system("pause");
            break;
        }
    }
}

// Function of data edit menu
void ViewUIDataMenu()
{
    int menu_item;

    while (true)
    {
        system("cls");

        cout << "\t Меню редактирования данных" << endl;
        cout << "1. Ввод новых данных" << endl;
        cout << "2. Удаление данных" << endl;
        cout << "3. Просмотр данных" << endl;
        cout << "4. Назад" << endl;
        cout << "\n(i) Введите пункт меню." << endl;

        menu_item = ValidateInput(menu_item, "> ");

        system("cls");

        switch (menu_item)
        {
        case 1:
            ViewUIAddNewData();
            system("pause");
            break;
        case 2:
            DeleteDataFromFile(g_file_path);
            system("pause");
            break;
        case 3:
            ReadDataFromFile(g_file_path);
            system("pause");
            break;
        case 4:
            return;
        default:
            cout << "(!) Неправильно выбран пункт меню." << endl;
            system("pause");
            break;
        }
    }
}

// Function for initialization of a configuration file
void InitConfigFile()
{
    bool is_exist = true;

    ifstream config_file("config.txt");

    // If the config file does not exist or is empty
    if (!config_file.good() || config_file.peek() == std::ifstream::traits_type::eof())
    {
        ofstream out_file("config.txt");

        out_file << "path=" << g_file_path << endl;

        // TO DO:
        // Here are the new configuration parameter keys (<key>=)...

        out_file.close();
        config_file.close();

        return;
    }

    string line;
    while (getline(config_file, line))
    {
        istringstream is_line(line);
        string key;
        if (getline(is_line, key, '='))
        {
            string value;
            if (getline(is_line, value))
                g_file_path = value;
        }
    }

    config_file.close();
}

// Function for editing a configuration file
void EditConfigFile(string _target_key, string _current_value)
{
    ifstream config_file("config.txt");
    ofstream temp_file("temp_config.txt");

    if (!config_file.good())
    {
        cout << "(!) Ошибка в работе с конфигурационным файлом. Попробуйте перезапустить программу." << endl;

        config_file.close();
        system("pause");

        return;
    }

    string line;
    while (getline(config_file, line))
    {
        istringstream is_line(line);
        string key;
        if (getline(is_line, key, '='))
        {
            if (_target_key == key)
            {
                temp_file << key + '=' + _current_value << endl;
            }
            else
            {
                string value;
                if (getline(is_line, value))
                    temp_file << key + '=' + value << endl;
            }
        }
    }

    config_file.close();
    temp_file.close();

    remove("config.txt"); // Delete the old file
    rename("temp_config.txt", "config.txt"); // Rename new file to the older file
}

// Function for creating a new file by user input
void CreateNewFile()
{
    string file_name, file_path, full_path;

    cout << "(i) Создание нового файла." << endl;
    cout << "(i) Укажите имя файла (например: \"filename.bin\")" << endl;
    cout << "> ";

    getline(cin, file_name);

    cout << "(i) Укажите путь к файлу. Он должен быть следующего формата: {Диск}:\\{КАТАЛОГ}" << endl;
    cout << "> ";
    
    getline(cin, file_path);

    full_path = file_path + "\\" + file_name;

    ofstream create_file(full_path);
    create_file.close();

    if (!create_file.good())
    {
        cout << "(!) Произошла ошибка при создании файла." << endl;
        system("pause");
        return;
    }

    EditConfigFile("path", full_path); // Edit key path in config file
    g_file_path = full_path; // Set new global path to file

    cout << "(i) Файл успешно создан." << endl;
    system("pause");
}

// Function for adding data to a file
void AddDataToFile(string _path)
{
    ofstream append_to_file(_path, ios::app | ios::binary);

    if (!append_to_file)
    {
        cout << "(!) Невозможно открыть файл." << endl;
        system("pause");
        return;
    }

    ifstream read_file(_path, ios::in | ios::binary);

    unsigned int file_length;

    Classroom buffer;

    bool is_active = true;
    while (is_active)
    {
        bool is_correct = true;

        cout << "(i) Ввод новых данных. " << endl;

        Classroom classroom = InputNewData();

        // Get a file length
        read_file.seekg(0, read_file.end);
        file_length = read_file.tellg();
        read_file.seekg(0, read_file.beg);

        for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
        {
            read_file.read((char*)&buffer, sizeof(Classroom));

            if (classroom.getNumber() == buffer.getNumber())
            {
                cout << "(!) В файле уже записана аудитория с таким номером: " << classroom.getNumber() << endl;
                cout << "(i) Недопустима запись аудиторий с одинаковым номером." << endl;
                is_correct = false;
                break;
            }
        }

        if (is_correct)
        {
            cout << "(?) Сохранить введённую запись? (Да - 1 / Нет - 0)" << endl;

            bool accept_input;
            accept_input = ValidateInput(accept_input, "> ");

            if (accept_input)
            {
                cout << "(i) Запись сохранена." << endl;
                append_to_file.write((char*)&classroom, sizeof(Classroom));
            }
        }

        cout << "(?) Желаете ввести ещё одну запись? (Да - 1 / Нет - 0)" << endl;
        is_active = ValidateInput(is_active, "> ");
    }
    
    read_file.close();
    append_to_file.close();

    if (!append_to_file.good())
    {
        cout << "(!) Произошла ошибка во время добавления новых данных в файл." << endl;
        system("pause");
        return;
    }

    SortByNumber(_path);
}

// Function for displaying the menu of adding new data
void ViewUIAddNewData()
{
    cout << "(i) Добавление новых данных." << endl;
    cout << "(?) Создать новый файл? (Да - 1 / Нет - 0)" << endl;

    bool create_new;
    create_new = ValidateInput(create_new, "> ");
    cin.ignore();

    system("cls");

    if (create_new)
    {
        CreateNewFile();
        system("cls");
    }

    AddDataToFile(g_file_path);
}

// Function for entering a new data structure
Classroom InputNewData()
{   
    Classroom classroom;

    unsigned int number;
    double area;
    unsigned int seats;
    string str_buffer;

    cout << "Введите необоходимые данные: " << endl;

    number = ValidateInput(number, "- Номер аудитории: ");
    classroom.setNumber(number);

    cout << "- Название отделения: ";
    cin.ignore();
    getline(cin, str_buffer);
    classroom.setDepartment(str_buffer);

    cout << "- Тип аудитории: ";
    getline(cin, str_buffer);
    classroom.setClroomType(str_buffer);

    area = ValidateInput(area, "- Площадь аудитории: ");
    classroom.setArea(area);

    seats = ValidateInput(seats, "- Количество мест в аудитории: ");
    classroom.setSeats(seats);

    return classroom;
}

// Function for reading data from a binary file
void ReadDataFromFile(string _path)
{
    ifstream read_file(_path, ios::in | ios::binary);

    if (!IsFileGood(read_file)) return;

    unsigned int file_length = 0;

    // Get a file length
    read_file.seekg(0, read_file.end);
    file_length = read_file.tellg();
    read_file.seekg(0, read_file.beg);

    ViewUITable(); // Show table column names

    Classroom buffer;

    // Fields for paginated data output
    size_t const block_size = 20;   // Size of block of data (number of items on one page)
    size_t elements_count = 0;      // The current number of items on the page

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        // Code fragment for outputting the next page or stopping reading from the file
        if (elements_count == block_size)
        {
            cout << "\n(?) Продолжить чтение данных? (Да - 1 / Нет - 0)" << endl;

            bool next = ValidateInput(next, "> ");

            if (next)
            {
                elements_count = 0;

                cout << endl;
                ViewUITable(); // Show table column names
            }
            else
                break;
        }

        OutputDataAsTable(buffer); // Show a data row from the read item

        elements_count++;
    }

    read_file.close();

    if (!read_file.good())
    {
        cout << "(!) Произошла ошибка во время чтения файла." << endl;
        system("pause");
        return;
    }

    cout << "\n(i) Чтение из файла успешно завершенно." << endl;

    return;
}

// Function for searching and deleting data by user input
// Function for deleting data from a file
void DeleteDataFromFile(string _path)
{
    unsigned int target_number;

    ifstream read_file(_path, ios::in | ios::binary);

    if (!IsFileGood(read_file)) return;

    ofstream temp_file("temp.bin", ios::out | ios::binary);

    cout << "(i) Удаление данных из файла." << endl;
    while (true)
    {
        cout << "(i) Введите номер аудитории, данные о которой хотите удалить." << endl;

        target_number = ValidateInput(target_number, "> ");
        
        cout << "(?) Удалить данные об указанной аудитории? (Да - 1 / Нет - 0)" << endl;

        bool accept_input;
        accept_input = ValidateInput(accept_input, "> ");
        cin.ignore();

        if (accept_input)
            break;
    }
    
    unsigned int file_length = 0;

    // Get a file length
    read_file.seekg(0, read_file.end);
    file_length = read_file.tellg();
    read_file.seekg(0, read_file.beg);

    Classroom buffer;
    bool is_data_found = false;

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        if (target_number == buffer.getNumber())
            is_data_found = true;
        else
            temp_file.write((char*)&buffer, sizeof(Classroom));
    }

    read_file.close();
    temp_file.close();

    remove(_path.c_str()); // Delete the old file
    rename("temp.bin", _path.c_str()); // Rename new file to the older file

    if (!read_file.good())
    {
        cout << "(!) Произошла ошибка во время чтения файла." << endl;
        system("pause");
        return;
    }

    if (is_data_found)
        cout << "(i) Искомые данные удалены." << endl;
    else
        cout << "(i) Искомые данные не найдены." << endl;
}

// Function for searching data by user input
// Searches for matches by Department and Classroom type
void GetDataByDepAndType()
{
    string target_department, target_clroom_type;

    bool accept_input = false;
    while (!accept_input)
    {
        cout << "(i) Укажите искомые параметры." << endl;
        cout << "- Отделение: ";
        cin.ignore();
        getline(cin, target_department);

        cout << "- Тип аудитории: ";
        getline(cin, target_clroom_type);

        cout << "(?) Применить введенные параметры? (Да - 1 / Нет - 0)" << endl;
        accept_input = ValidateInput(accept_input, "> ");
    }

    system("cls");

    ifstream read_file(g_file_path, ios::in | ios::binary);

    if (!IsFileGood(read_file)) return;

    cout << "(i) Вывод данных по следующим параметрам:" << endl;
    cout << "- Отделение: " << target_department << endl;
    cout << "- Тип аудитории: " << target_clroom_type << endl << endl;

    unsigned int file_length;

    // Get a file length
    read_file.seekg(0, read_file.end);
    file_length = read_file.tellg();
    read_file.seekg(0, read_file.beg);

    Classroom buffer;
    bool is_data_found = false;

    ViewUITable(); // Show table column names

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        if (buffer.getDepartment() == target_department && buffer.getClroomType() == target_clroom_type)
        {
            OutputDataAsTable(buffer); // Show a data row from the read item
            is_data_found = true;
        }
    }

    read_file.close();

    if (!read_file.good())
    {
        cout << "(!) Произошла ошибка во время чтения файла." << endl;
        system("pause");
        return;
    }

    if (!is_data_found)
    {
        system("cls");
        cout << "(i) Искомые данные не найдены." << endl;
    }

    cout << "\n(i) Чтение из файла успешно завершенно." << endl;
}

// Function for searching the biggest value of the classroom area
void GetDataByMaxArea()
{
    double max_area = 0.0;

    cout << "(i) Поиск аудиторий с самой большой площадью." << endl;

    ifstream read_file(g_file_path, ios::in | ios::binary);

    if (!IsFileGood(read_file)) return;

    unsigned int file_length;

    // Get a file length
    read_file.seekg(0, read_file.end);
    file_length = read_file.tellg();
    read_file.seekg(0, read_file.beg);

    Classroom buffer;
    bool is_data_found = false;

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        if (buffer.getArea() > max_area)
            max_area = buffer.getArea();
    }

    read_file.seekg(0, read_file.beg); // Back to file start

    ViewUITable(); // Show table column names

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        if (buffer.getArea() == max_area)
        {
            OutputDataAsTable(buffer); // Show a data row from the read item
            is_data_found = true;
        }
    }

    read_file.close();

    if (!read_file.good())
    {
        cout << "(!) Произошла ошибка во время чтения файла." << endl;
        system("pause");
        return;
    }

    if (!is_data_found)
    {
        system("cls");
        cout << "(i) Искомые данные не найдены." << endl;
    }

    cout << "\n(i) Чтение из файла успешно завершенно." << endl;
}

// Function for searching data by user input
// Search for classrooms that contain the specified number of seats (or more)
void GetDataBySeats()
{
    unsigned int target_seats;

    bool accept_input = false;
    while (!accept_input)
    {
        cout << "(i) Укажите количество мест, которое должна вмещать аудитория." << endl;
        target_seats = ValidateInput(target_seats, "> ");

        cout << "(?) Применить введенные параметры? (Да - 1 / Нет - 0)" << endl;
        accept_input = ValidateInput(accept_input, "> ");
    }

    system("cls");

    ifstream read_file(g_file_path, ios::in | ios::binary);

    if (!IsFileGood(read_file)) return;

    cout << "(i) Вывод аудиторий, которые вмещают указанное количество мест: " << target_seats << endl;

    unsigned int file_length;

    // Get a file length
    read_file.seekg(0, read_file.end);
    file_length = read_file.tellg();
    read_file.seekg(0, read_file.beg);

    ViewUITable(); // Show table column names

    Classroom buffer;
    bool is_data_found = false;

    for (size_t i = 0; i < file_length / sizeof(Classroom); i++)
    {
        read_file.read((char*)&buffer, sizeof(Classroom));

        if (buffer.getSeats() >= target_seats)
        {
            OutputDataAsTable(buffer); // Show a data row from the read item
            is_data_found = true;
        }
    }

    read_file.close();

    if (!read_file.good())
    {
        cout << "(!) Произошла ошибка во время чтения файла." << endl;
        system("pause");
        return;
    }

    if (!is_data_found)
    {
        system("cls");
        cout << "(i) Искомые данные не найдены." << endl;
    }

    cout << "\n(i) Чтение из файла успешно завершенно." << endl;
}

// Function that checks the file for correctness
bool IsFileGood(ifstream& _ifs)
{
    if (!_ifs)
    {
        cout << "(!) Невозможно открыть файл." << endl;
        system("pause");
        return false;
    }

    unsigned int file_length = 0;

    // Get a file length
    _ifs.seekg(0, _ifs.end);
    file_length = _ifs.tellg();
    _ifs.seekg(0, _ifs.beg);

    if (file_length == 0)
    {
        cout << "(i) Файл данных пуст." << endl;
        system("pause");
        return false;
    }

    return true;
}

// Function for displaying the names of a table columns
void ViewUITable()
{
    cout.setf(ios::left);
    cout.width(7);
    cout << "№";

    cout.setf(ios::left);
    cout.width(40);
    cout << "ОТДЕЛЕНИЕ";

    cout.setf(ios::left);
    cout.width(40);
    cout << "ТИП АУДИТОРИИ";

    cout.setf(ios::left);
    cout.width(10);
    cout << "ПЛОЩАДЬ";

    cout.setf(ios::left);
    cout.width(10);
    cout << "МЕСТА" << endl;
}

// Function for displaying data in the form of a table
void OutputDataAsTable(Classroom _data)
{
    cout.setf(ios::left);
    cout.width(7);
    cout << _data.getNumber();

    cout.setf(ios::left);
    cout.width(40);
    cout << _data.getDepartment();

    cout.setf(ios::left);
    cout.width(40);
    cout << _data.getClroomType();

    cout.setf(ios::left);
    cout.width(10);
    cout << _data.getArea();

    cout.setf(ios::left);
    cout.width(10);
    cout << _data.getSeats() << endl;
}

// Function for changing the file path
void SetPathToFile(string& _path)
{
    bool to_change;

    cout << "(i) Если программе не удается открыть файл, который существует, попробуйте запустить программу от имени администратора." << endl;
    cout << "(i) Текущий путь к файлу данных: " << _path << endl;
    cout << "(?) Желаете его изменить? (Да - 1 / Нет - 0)";

    to_change = ValidateInput(to_change, "\n> ");

    if (to_change)
    {
        cout << endl << "(i) Файл должен иметь расширение (формат) .bin для корректной работы." << endl;
        cout << "(i) Укажите путь к файлу. Он должен быть следующего формата: {Диск}:\\{КАТАЛОГ}\\{ФАЙЛ}" << endl;
        cout << "> ";
        cin.ignore();
        getline(cin, _path);
        EditConfigFile("path", _path);
    }
}

// Function for sorting data in a binary file from min number to max number of classroom
void SortByNumber(string _path)
{
    fstream file;
    file.open(_path, ios::out | ios::in | ios::binary);

    unsigned int file_length;

    // Get a file length
    file.seekg(0, file.end);
    file_length = file.tellg();
    file.seekg(0, file.beg);

    Classroom buffer1, buffer2;

    for (int i = 1; i < (file_length / sizeof(Classroom)); i++)
    {
        file.seekp(sizeof(Classroom) * i, ios::beg);
        file.read((char*)&buffer1, sizeof(Classroom));

        for (int j = 0; j < i; j++)
        {
            file.seekp(sizeof(Classroom) * j, ios::beg);
            file.read((char*)&buffer2, sizeof(Classroom));

            if (buffer1.getNumber() < buffer2.getNumber())
            {
                file.seekp(sizeof(Classroom) * i, ios::beg);
                file.write((char*)&buffer2, sizeof(Classroom));

                file.seekp(sizeof(Classroom) * j, ios::beg);
                file.write((char*)&buffer1, sizeof(Classroom));

                buffer1 = buffer2;
            }
        }
    }

    file.close();
}

// Function for validate user input
template<typename T>
T& ValidateInput(T& _val, string _message)
{
    while (true)
    {
        cout << _message;
        if (cin >> _val)
            break;
        else
        {
            cout << "(!) Введите корректное значение." << endl;
            cin.clear();
            cin.ignore(32726, '\n');
        }
    }

    return _val;
}
