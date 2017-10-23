 #include <fstream> // Заголовочный файл для класса ofstream
 #include <experimental/filesystem> 
 #include <iostream>
 #include <cstring>

 using namespace std;
 namespace fs = experimental::filesystem; //подключение пространства имён fs

 int main() 
 {
 	try {
 		string address;
 		cout << "Enter path of file" << endl;
 		cin >> address; //Указываем путь к файлу

 		if (fs::exists(address) == 0) // Проверка существования файла по введенному адресу
 			throw runtime_error("File does not find!");

 		const fs::path filePath = address; // Указываем путь к файлу 
 		const fs::path textFilename = filePath.filename(); // Получаем имя файла
		auto  writeTimePoint = fs::last_write_time(filePath); 			// Получаем время последнего изменения файла 
  		time_t cftime = decltype(writeTimePoint)::clock::to_time_t(writeTimePoint);   // Переделаем данные времени в строку для вывода

  		//ofstream - класс, используемый для записи данных в файл
		ofstream(filePath) << "Filename:\t" << textFilename << endl << "Modification date:\t" << asctime(localtime(&cftime)) << "Size:\t" << fs::file_size(filePath) << " byte" << endl; // Запись информации в файл
 	}

 	catch (const exception& e) 
 	{
 		cout << e.what() << endl;
 	}
 	return 0;
 }
