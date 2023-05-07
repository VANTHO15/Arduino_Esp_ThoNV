//Khai bao thu vien
#include <Arduino_FreeRTOS.h>   //Thu vien FreeRTOS
#include <task.h>
#include <queue.h>
#include <Servo.h>              //Khai báo thư viện sử dụng cho động cơ Servo dung cho DOOR
#include <LiquidCrystal_I2C.h>  // Khai báo thư viện LCD sử dụng I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 địa chỉ LCD, 16 cột và 2 hàng
#include <Keypad.h>                 // Khai báo thư viện Keypad
#include <EEPROM.h>

//Định nghĩa các chân
#define buzzGasPin 22     //22 là Pin của buzzer dùng cho MQ2
#define ledGasPin 23      //23 là Pin của LED dùng cho MQ2
#define buzzDoorPin 24    //Pin của buzzer dùng cho Door (báo động)
#define valueDigitalPin 3 //Pin nhận giá trị Digital của MQ2
////..

//Queue
  QueueHandle_t xQueueGas;
//..

//Định nghĩa các biến
////Dùng cho KEYPAD 4x4
const byte ROWS = 4;  //4 Hàng của bàn phím
const byte COLS = 4;  //4 cột của bàn phím

////Định nghĩa bản đồ phím
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

byte rowPins[ROWS] = { 12, 11, 10, 9 }; //Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 8,7,6,5 }; //Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //Định nghĩa Keypad gán cho keypad

//Khai báo các Task
void TaskEnterPassword( void *pvParameters );
////Queue
void TaskSensorSender( void *pvParameters );
void TaskSensorReceiver( void *pvParameters );
////..

/*.......................................*/

char str[4] = {' ', ' ', ' ', ' '};

void setup( void )
{
  Serial.begin( 9600 ); //Mở cổng Serial để giao tiếp
  Serial.println( "\nIn Setup function\n" );  
  lcd.begin();  //Khai báo sử dụng LCD
//////////
  char STR[4] = {'0', '0', '0', '0'}; //Cài đặt mật khẩu tùy ý
  int addr = 0;
  for( addr = 0; addr <= 3; addr++ )
  {
    for( int v = 0; v <= 3; v++ )
    {
      EEPROM.write( addr, STR[v]);
      delay( 5 );
    }
  }
///////////

//xQueueCreate
  xQueueGas = xQueueCreate( 3, sizeof( boolean )); //Queue lưu tối đa 3 dữ liệu khí gas với kiểu dữ liệu boolean
//..

    if( xQueueGas != NULL )
    {
      xTaskCreate( TaskSensorSender, "Send GasSS to Queue", 128, NULL, 1, NULL); //Task Gửi dữ liệu Gas từ cảm biến vào Queue
      xTaskCreate( TaskSensorReceiver, "Read SS Value from Queue", 128, NULL, 2, NULL); //Task Nhận dữ liệu Queue
      xTaskCreate( TaskEnterPassword, "Enter Password", 128, NULL, 3, NULL ); //Task nhập mật khẩu
      vTaskStartScheduler();
    }
    else
    {}
    for( ;; );
}

/*__________*/
void loop()
{
  // Empty. Things are done in Tasks.
}
/*__________*/

/*..... Định nghĩa các Task .....*/
// Enter Password
void TaskEnterPassword( void *pvParameters )
{
  ( void ) pvParameters;
  
  /*
     Đọc giá trị từ KEYPAD.
     In ra màn hình các ký tự vừa nhập sau đó hiển thị dấu "*" thay thế để bảo mật
     Dựa vào các giá trị đọc được, đặt biến count = 1 để vào vòng so sánh với mật khẩu đã cài đặt
        Nếu đúng, mở cửa.
        Nếu sai, vào vòng sai mật khẩu:
          * Mật khẩu được nhập sai tối đa 5 lần
          * Sai lần thứ 5 sẽ bị tạm khóa 05 phút
          * Sau 5 phút, trở lại vòng nhập mật khẩu
     Thiết lập thêm một số tùy chọn đặc biệt của các phím
        Nếu bấm phím '#': Khóa cửa, về lại nhập mật khẩu
        Nếu bấm phím 'A': Nhập lại mật khẩu
  */

  Servo doorServo;  //Khởi tạo biến doorServo để gọi hàm sử dụng động cơ Servo
  doorServo.attach( 2 );  //Khai báo Pin 2 là Pin điều khiển động cơ
  
  pinMode( buzzDoorPin, OUTPUT );
  digitalWrite( buzzDoorPin, LOW );
  
  int setCountDown = 300; //Số giây đếm ngược khi bị VO HIEU HOA
  int countDown = 0; //Biến đếm ngược
  char key = 0;         //Biến nhận giá trị bàn phím
  int wrongCounter = 0; //Biến đếm số lần nhập sai
  int i;  //Biến đếm số lượng ký tự được nhập vaò từ KEYPAD
  int count = 0;  //Biến chuyển vòng lặp

  char strROM[4] = {' ', ' ', ' ', ' '};
  
  ////Trạng thái ban đầu
    lcd.clear(); //xóa màn hình
    lcd.setCursor( 1,0 ); //Đặt con trỏ tại cột 1 hàng 0
    lcd.print( "Enter Password" );  //in ra màn hình
  
  for( ;; )
  { 
    key = keypad.getKey(); //Ký tự nhập vào sẽ gán cho biến key
    ////nhập mật khẩu
    if( key )
    {
      lcd.backlight();  //Bật đèn nền LCD mỗi khi có nút được nhấn (dùng cho trường hợp LCD đang tắt để tiết kiệm NL
      if( i == 0 )
      {
        str[0] = key; //ghi ký tự nhập vào mảng lưu str
        tone( buzzDoorPin, 500, 200 ); //âm thanh bàn phím
        lcd.setCursor( 6, 1 );  //Đặt con trỏ tại cột 6 hàng 1 (có 2 hàng là 0 và 1)
        lcd.print( str[0] );
        delay( 300 ); //Ký tự hiển thị trên màn hình LCD trong 0.3s
        lcd.setCursor( 6, 1 );
        lcd.print( "*" ); //Mật khẩu được che bởi dấu *
      }
      if( i == 1 )
      {
        str[1] = key;
        tone( buzzDoorPin, 500, 200 );
        lcd.setCursor( 7, 1 );
        lcd.print( str[1] );
        delay( 300 );
        lcd.setCursor( 7, 1 );
        lcd.print( "*" );
      }
      if( i == 2 )
      {
        str[2] = key;
        tone( buzzDoorPin, 500, 200 );
        lcd.setCursor( 8, 1 );
        lcd.print( str[2] );
        delay( 300 );
        lcd.setCursor( 8, 1 );
        lcd.print( "*" );
      }
      if( i == 3 )
      {
        str[3] = key;
        tone( buzzDoorPin, 500, 200 );
        lcd.setCursor( 9, 1 );
        lcd.print( str[3] );
        delay( 300 );
        lcd.setCursor( 9, 1 );
        lcd.print( "*" );
        count = 1;
      }
      i++;
    }
    ////kiểm tra mật khẩu
    if( count == 1 )
    {
      for( int addr = 0; addr <=3; addr++ )
      {
        for( int u = 0; u <=3; u++ )
        {
          strROM[u] = EEPROM.read(addr);
          delay( 5 );
        }
      }
      //////so sánh với mật khẩu đã đặt
      if( str[0] == strROM[0] &&
          str[1] == strROM[1] &&
          str[2] == strROM[2] &&
          str[3] == strROM[3] )
        {
          lcd.clear(); //Xóa màn hình
          lcd.setCursor( 4, 0 );
          lcd.print( "Correct!" );
          tone( buzzDoorPin, 2000, 1000 ); //Bật buzzer trong 1000ms ở 3000Hz
          vTaskDelay(1000/portTICK_PERIOD_MS);  //Đợi 1s
          doorServo.write( 0 ); //Động cơ quay 0 đọ (Mở cửa)
          lcd.clear();
          lcd.setCursor( 5, 0 );
          lcd.print( "Opened" );
          lcd.setCursor( 4, 1 );
          lcd.print( "Welcome!" );
          vTaskDelay(2000/portTICK_PERIOD_MS);  //Đợi 2s
          lcd.clear();
          lcd.noBacklight();  //Tắt đèn nền
          lcd.setCursor(1,0);
          lcd.print("Enter Password");
          //////Về lại trạng thái ban đầu
          i = 0;
          count = 0;
          wrongCounter = 0;
        }
        else  //Nếu mật khẩu nhập vào bị sai
        {
          lcd.clear();
          lcd.setCursor( 3, 0 );
          lcd.print( "Incorrect!" );
          wrongCounter++;
          if( wrongCounter != 0 )
          {
            lcd.clear();
            lcd.setCursor( 3, 0 );
            lcd.print( "Try Again!" );
            vTaskDelay(1000/portTICK_PERIOD_MS);
            lcd.clear();
            lcd.setCursor( 1, 0 );
            lcd.print( "Enter Password" );
            count = 0;
            i = 0;
            if( wrongCounter == 4 )
            {
              lcd.clear();
              lcd.setCursor( 1, 0 );
              lcd.print( "Enter Password" );
              count = 0;
              i = 0;
            }
            if( wrongCounter == 5 )
            {
              lcd.clear();
              lcd.setCursor( 2, 0 );
              lcd.print( "VO HIEU HOA!" );
              tone( buzzDoorPin, 4000, 3000 );
              vTaskDelay(4000/portTICK_PERIOD_MS);
              for( countDown = setCountDown; countDown >= 0; countDown-- )
              {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("VO HIEU HOA!");
                lcd.setCursor(7, 1);
                lcd.print(countDown);
                vTaskDelay(1000/portTICK_PERIOD_MS);
              }
              delay( 1000 );
              lcd.clear(); //xóa màn hình
              lcd.setCursor( 1,0 ); //Đặt con trỏ tại cột 1 hàng 0
              lcd.print( "Enter Password" );  //in ra màn hình
              count = 0;
              i = 0;
              wrongCounter = 0;
            }
          }
        }
    }
