void setup() {

  int myEraser = 7;
  TCCR2B &= ~ myEraser;   // 2 la time 2 chan 9 10
  int myPrescaler = 3;   // 011
  TCCR2B |= myPrescaler; // TCCR2B se bang 011
  pinMode ( 22, OUTPUT ) ;
  digitalWrite(22, 1);
  analogWrite(23, 65535);
  // bay h co tan so moi tren 9 va 10
  //prescaler = 1 ---> PWM frequency is 31000 Hz
  //prescaler = 2 ---> PWM frequency is 4000 Hz
  //prescaler = 3 ---> PWM frequency is 490 Hz (default value)
  //prescaler = 4 ---> PWM frequency is 120 Hz
  //prescaler = 5 ---> PWM frequency is 30 Hz
  //prescaler = 6 ---> PWM frequency is <20 Hz
}

void loop() {

}

//1) Arduino 2560 có 12 chân hỗ trợ PWM. Chúng bao gồm từ 2 đến 13.
//
//2) tần số mặc định của PWM là 490 Hz cho tất cả các chân, ngoại trừ chân 13 và 4,
//có tần số là 980 Hz (tôi đã kiểm tra bằng máy hiện sóng).
//
//3) Để thay đổi tần số trên chân 'A', chúng ta phải thay đổi một số giá trị trong bộ định thời
//(hoặc thanh ghi), điều khiển chân 'A'. Đây là danh sách các bộ định thời trong Arduino Mega 2560:
//
//bộ định thời 0 (điều khiển chân 13, 4);
//bộ định thời 1 (điều khiển chân 12, 11);
//bộ định thời 2 (điều khiển chân 10, 9);
//bộ đếm thời gian 3 (điều khiển chân 5, 3, 2);
//bộ đếm thời gian 4 (điều khiển chân 8, 7, 6);
//
//Như bạn có thể thấy, một bộ đếm thời gian nhất định điều khiển nhiều hơn một chân (mọi thay đổi về bộ hẹn giờ sẽ ảnh hưởng đến tất cả các chân tùy thuộc vào nó!).
//
//4) Bạn có thể truy cập bộ đếm thời gian chỉ cần thay đổi mã của bạn (thông thường trong cài đặt ()), giá trị của biến TCCRnB, trong đó 'n' là số thanh ghi. Vì vậy, nếu chúng ta muốn thay đổi tần số PWM của chân 10 và 9, chúng ta sẽ phải tác động trên TCCR2B.
//
//5) TCCRnB là một số 8 bit. Ba bit đầu tiên (từ phải sang trái!) Được gọi là CS02, CS01, CS00 và chúng là những bit chúng ta phải thay đổi.
//Trên thực tế, các bit đó đại diện cho một số nguyên (từ 0 đến 7) được gọi là 'prescaler', Arduino sử dụng để tạo tần số cho PWM.
//
//6) Trước hết, chúng ta phải xóa ba bit này, tức là tất cả chúng phải được đặt thành 0:
//
//int myEraser = 7; // đây là 111 trong hệ nhị phân và được sử dụng như một công cụ tẩy
//TCCR2B & = ~ myEraser; // phép toán này (VÀ cộng với KHÔNG),
//
//7) bây giờ CS02, CS01, CS00 đã rõ ràng, chúng tôi viết trên chúng một giá trị mới:
//
//int myPrescaler = 3; // đây có thể là một số trong [1, 6]. Trong trường hợp này, 3 tương ứng trong hệ nhị phân với 011.
//TCCR2B | = myPrescaler; // phép toán này (OR), thay thế ba bit cuối cùng trong TCCR2B bằng giá trị mới 011 của
//
//số 8)chúng ta, bây giờ chúng ta có tần số PWM mới trên chân 9 và 10!
//
//
//Tôi đã đăng ký các giá trị đó trên tất cả các chân PWM, thay đổi giá trị của prescaler (ngoại lệ duy nhất là các chân 13 và 14, xem sau):
//
//prescaler = 1 ---> Tần số PWM là 31000 Hz
//prescaler = 2 ---> Tần số PWM là Bộ định mức 4000 Hz
//= 3 ---> Tần số PWM là 490 Hz (giá trị mặc định) Bộ định mức trước
//= 4 ---> Tần số PWM là 120 Hz Bộ định mức trước
//= 5 ---> Tần số PWM là 30 Hz
//prescaler = 6 ---> Tần số PWM <20 Hz
//
//(các prescaler bằng t 0 hoặc 7 đều vô dụng).
//
//Các giá trị bộ đếm trước đó phù hợp với tất cả các bộ định thời (TCCR1B, TCCR2B, TCCR3B, TCCR4B)
//ngoại trừ bộ định thời 0 (TCCR0B). Trong trường hợp này các giá trị là:
//
//prescaler = 1 ---> Tần số PWM là 62000 Hz
//prescaler = 2 ---> Tần số PWM là 7800 Hz
//prescaler = 3 ---> Tần số PWM là 980 Hz (giá trị mặc định)
//prescaler = 4 ---> Tần số PWM là 250 Hz
//prescaler = 5 ---> Tần số PWM là 60 Hz
//prescaler = 6 ---> Tần số PWM là <20 Hz
//
//Lưu ý rằng bộ định thời 0 là bộ định thời dựa vào tất cả các chức năng thời gian trong Arduino:
//tức là, nếu bạn thay đổi bộ đếm thời gian này, hàm như delay () hoặc millis () sẽ tiếp tục hoạt 
//động nhưng ở một khoảng thời gian khác (nhanh hơn hoặc chậm hơn !!!)
