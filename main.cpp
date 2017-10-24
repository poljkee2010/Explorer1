#include <fstream> // Заголовочный файл для класса ofstream
#include <experimental/filesystem>
#include <iostream>
#include <cstring>

using namespace std;
namespace fs = experimental::filesystem; //подключение пространства имён fs
string EXPLORER_LOG_PATH = "log.txt";

int main()
{
 try {
   string address;
   cout << "Enter path of file" << endl;
   cin >> address; //Указываем путь к файлу

   //Проверка на то, является ли файл директорией
   if(!fs::is_directory(address))
   {
     throw runtime_error("ERROR: Type of file - not directory");
   }

   if (fs::exists(address) == 0) // Проверка существования файла по введенному адресу
     throw runtime_error("File does not find!");

   const fs::path filePath = address; // Указываем путь к файлу
   const fs::path textFilename = filePath.filename(); // Получаем имя файла
   auto  writeTimePoint = fs::last_write_time(filePath); 			// Получаем время последнего изменения файла
   time_t cftime = decltype(writeTimePoint)::clock::to_time_t(writeTimePoint);   // Переделаем данные времени в строку для вывода


   //ofstream - класс, используемый для записи данных в файл
   ofstream out(EXPLORER_LOG_PATH);
   out << "Filename:\t" << textFilename << endl;	//Запись информации в файл
   out << "Modification date:\t" << asctime(localtime(&cftime)) << endl;
   out << "Size:\t" << fs::file_size(EXPLORER_LOG_PATH) << " byte" << endl;
   out.close(); //Закрытие потока
 }

 catch (const exception& e)
 {
   cout << e.what() << endl;
 }
 return 0;
}
