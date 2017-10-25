#include <fstream> // Заголовочный файл для класса ofstream
#include <experimental/filesystem>
#include <iostream>
#include <cstring>

using namespace std;
namespace fs = experimental::filesystem; //подключение пространства имён fs
string EXPLORER_LOG_PATH = "log.txt"; //для записи информации о переданном файле

int main()
{
	try {
		string address;
		cout << "Enter path of file" << endl;
		cin >> address; //Указываем путь к файлу

		if (fs::is_directory(address)) 	//Проверка на то,ссылается ли введённый путь на каталог
			throw runtime_error("ERROR: Type of file - directory");

		if (fs::exists(address) == 0)	//Проверка существования файла по введенному адресу
			throw runtime_error("ERROR: File does not find!");

		const fs::path filePath = address; // Указываем путь к файлу
		const fs::path textFilename = filePath.filename(); // Получаем имя файла
		auto  writeTimePoint = fs::last_write_time(filePath); 			// Получаем время последнего изменения файла
		time_t cftime = decltype(writeTimePoint)::clock::to_time_t(writeTimePoint);   // Переделаем данные времени в строку для вывода


		//ofstream - класс, используемый для записи данных в файл заданный с помощью переменной окружения EXPLORER_LOG_PATH
		ofstream out(EXPLORER_LOG_PATH); //Запись информации в файл log.txt
		out << "Filename:\t" << textFilename << endl;	
		out << "Modification date:\t" << asctime(localtime(&cftime)) << endl;
		out << "Size:\t" << fs::file_size(filePath) << " byte" << endl;
		out.close(); //Закрытие потока
	}

	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
