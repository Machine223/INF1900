#include "string.h"

string::string(){
	char start[] = "STRING: In the constructor...";
	dev_warn(start, sizeof(start));

    clear();

	char done[] = "STRING: string() Done. ";
	dev_warn(done, sizeof(done));
}

string::string(char data[], uint16_t size){
	char start[] = "STRING: In the constructor with data...";
	dev_warn(start, sizeof(start));

    setData(data, size);
    
	char done[] = "STRING: string(data) Done. ";
	dev_warn(done, sizeof(done));
}

char* string::getData(){
	char start[] = "STRING: Getting data...";
	dev_warn(start, sizeof(start));
    return char_ptr_;
}

void string::setData(char data [], uint16_t size){
	char start[] = "STRING: Setting data...";
	dev_warn(start, sizeof(start));

    size_ = size;
    char_ptr_ = (char*)data;
    
	char done[] = "STRING: setData() Done. ";
	dev_warn(done, sizeof(done));
}

uint16_t string::getSize(){
	char start[] = "STRING: Getting Size...";
	dev_warn(start, sizeof(start));

    return size_;
    
	char done[] = "STRING: getSize() Done.";
	dev_warn(done, sizeof(done));
}

void string::clear(){
	char start[] = "STRING: Clearing the string...";
	dev_warn(start, sizeof(start));

    char blank = ' ';
    char_ptr_ = &blank;
    size_ = 0;
    
	char done[] = "STRING: clear() Done. ";
	dev_warn(done, sizeof(done));
}