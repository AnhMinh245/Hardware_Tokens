#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define PASSWORD "1234"  // Mật khẩu được đặt là "1234"

void setup() 
{
  Serial.begin(9600);   // Khởi tạo giao tiếp serial
  SPI.begin();      // Khởi tạo bus SPI
  mfrc522.PCD_Init();   // Khởi tạo MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop() 
{
  // Tìm kiếm thẻ mới
  if (!mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  // Chọn một trong các thẻ
  if (!mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  // Hiển thị UID trên serial monitor
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  
  // Kiểm tra mật khẩu
  Serial.print("Enter password: ");
  while (Serial.available() <= 0); // Đợi người dùng nhập mật khẩu
  String password = Serial.readStringUntil('\n'); // Đọc dữ liệu từ Serial
  password.trim(); // Xóa khoảng trắng đầu và cuối chuỗi
  
  if (password == PASSWORD) // So sánh mật khẩu nhập vào với mật khẩu đúng
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
  else
  {
    Serial.println("Access denied");
    delay(3000);
  }
}
