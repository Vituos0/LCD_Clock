1. Giới thiệu
 1.1. Đặt vấn đề
Tiêu chí công suất thấp đã trở thành yếu tố ngày càng quan trọng và được dùng để so sánh giữa các thiết bị cùng phân khúc thị trường. Đặc biệt, đối với các ứng dụng dùng Pin, thiết bị di động (smart watch, smart phone, laptop, …), thiết bị dùng nguồn năng lượng từ tín hiệu không dây (contactless card, RFID card, …), … thì việc tiêu thụ công suất thấp đến cực thấp (ultra-low power) hay siêu thấp (extreme-low power) là trở thành yêu cầu tối quan trọng.
Nếu hai hệ thống tương đương nhau về chức năng và hiệu suất thì hệ thống nào tiêu thụ công suất ít hơn thì hệ thống đó có hiệu quả sử dụng năng lượng (power efficient) tốt hơn.
Chú ý rằng, đối với một hệ thống, “công suất thấp” phải đi đôi với “hiệu quả sử dụng năng lượng”. Một hệ thống rơi vào một trong hai trường hợp sau đây đều bị đánh giá là có hiệu quả sử dụng năng lượng thấp:
	Một hệ thống tiêu thụ công suất rất thấp nhưng xử lý chậm chạp, hiệu năng kém hoặc không đủ đáp ứng nhu cầu ứng dụng.
	Một hệ thống xử lý cực nhanh, thời gian xử lý trung bình đáp ứng gần như 100% các yêu cầu của ứng dụng nhưng tiêu thụ công suất gấp nhiều lần các hệ thống khác cùng loại.  
Hình 1.1. Thiết kế Low Power cho ESP32
Như vậy, việc thiết kế công suất thấp cần được cân bằng với hiệu quả xử lý. Điều này dẫn đến phạm vi ứng dụng các kỹ thuật công suất thấp trong hệ thống sẽ khác nhau. 

1.2. Mục tiêu nghiên cứu
       
     Trong bài nghiên cứu của nhóm, chúng em tập trung nghiên cứu vào thiết kế hệ thống cũng như chip ESP32. Mục tiêu đề ra:

	Tìm hiểu cấu hình, phương thức hoạt động của các module để tiết kiệm năng lượng. Điển hình là module wifi tiêu tốn rất nhiều năng lượng, nhưng nếu không hoạt động thì không thể gửi nhận tín hiệu -> vẫn sử dụng module wifi nhưng với cách tiếp cận khác để tiếp cận năng lượng
	Tìm hiểu về hardware của hệ thống công suất thấp, các linh kiện sử dụng trong low power design -> Cách thiết kế hệ thống low power sử dụng ESP32
	Xây dựng một hệ thống đơn giản, đo đạc được số liệu cụ thể -> So sánh với các thông số lý thuyết
	Tiến hành thảo luận và đưa ra kết luận 
1.3. Phạm vi nghiên cứu
Ở chủ đề nghiên cứu này, nhóm chúng em sẽ tập trung vào ESP32 và các modules liên quan:

   Các chế độ nghỉ của ESP32: 
	Active mode
	Modem sleep
	Light sleep
	Deep sleep
	Hibernation mode
   Các cơ chế đánh thức ESP32
	Timer wake-up, external wake up:
	Các chuẩn giao tiếp không dây
	Khả năng đánh thức 







2. Cơ sở lý thuyết
2.1. Khái niệm: 
Low power design là một phương pháp thiết kế để giảm tiêu thụ điện năng của hệ thống điện tử. Việc tiết kiệm năng lượng là một yếu tố quan trọng trong các ứng dụng điện tử hiện đại, đặc biệt là trong các ứng dụng IoT và các thiết bị di động. Với các thiết bị này, việc tiêu thụ điện năng phải được giảm thiểu để kéo dài tuổi thọ của pin, giảm chi phí năng lượng và tăng tính di động.
 Lợi ích:
	Giảm chi phí sản xuất và vận hành.
	Giảm sự nóng lên của hệ thống.
	 Tăng độ tin cậy và độ bền của thiết bị.
	Giảm tác động đến môi trường.
Với sự phát triển của IoT và các thiết bị di động, low power design trở thành một yếu tố quan trọng trong việc thiết kế các hệ thống điện tử. Do đó, việc nghiên cứu và phát triển các phương pháp low power design càng trở nên cần thiết để đáp ứng nhu cầu của thị trường và xã hội.
2.2. Cách thực hiện
 Trên Hardware:
* Sử dụng các thành phần tiêu thụ điện năng thấp, tối ưu hóa định dạng mạch 
* Tối ưu hóa kích thước và số lượng thành phần
* Sử dụng kỹ thuật điều chỉnh điện áp
 Trên Firmware:
* Sử dụng kỹ thuật giảm tần số hoạt động.
* Tối ưu hóa các thuật toán xử lý
Tóm lại, để thiết kế mạch điện tử tiêu thụ điện năng thấp, cần kết hợp cả phần hardware và firmware để đạt được hiệu quả tiết kiệm năng lượng tối đa.
 

2.3 Giới thiệu chung về ESP32
2.3. Tổng quan vể ESP32
 ESP32 là một vi điều khiển Wi-Fi và Bluetooth đa chức năng được sản xuất bởi công ty Espressif Systems. Nó là phiên bản tiếp theo của ESP8266, với nhiều tính năng mới và cải tiến. ESP32 được trang bị hai lõi xử lý Tensilica Xtensa LX6, đồng hồ tối đa 240 MHz và bộ nhớ flash lên đến 4 MB. Nó cũng hỗ trợ Wi-Fi 802.11 b/g/n, Bluetooth 4.2 và Bluetooth Low Energy (BLE).

Hình 2.3. Vi điều khiển ESP32
Các tính năng khác của ESP32 bao gồm:
34 chân IO có thể được gán các chức năng khác nhau như đầu vào analog, đầu vào số, đầu ra PWM và I2C/SPI/UART.
Hỗ trợ các giao thức như TCP/IP, HTTP, SSL/TLS, MQTT, CoAP, SPI.
Hỗ trợ các tính năng bảo mật như AES, SHA-2, RSA, ECC, SSL/TLS.
Hỗ trợ OTA (Over-The-Air) để cập nhật phần mềm từ xa.
Hỗ trợ tạo bảng giờ thời gian thực (RTC) với độ chính xác cao.
2.3.1. CPU
	CPU: Xtensa Dual-Core LX6 microprocessor chạy hệ 32 bit
	Tốc độ xử lý từ 160 MHz đến 240 MHz
	ROM: 448 Kb
	Tốc độ xung nhịp từ 40 Mhz ÷ 80 Mhz (có thể tùy chỉnh khi lập trình)
	RAM: 520 Kb SRAM liền chip. Trong đó 8 Kb RAM RTC tốc độ cao – 8 Kb RAM RTC tốc độ thấp (dùng ở chế độ DeepSleep).
2.3.2. Các giao tiếp hỗ trợ
	2 bộ chuyển đổi số sang tương tự (DAC) 8 bit
	18 kênh bộ chuyển đổi tương tự sang số (ADC) 12 bit.
	2 cổng giao tiếp I²C
	3 cổng giao tiếp UART
	3 cổng giao tiếp SPI (1 cổng cho chip FLASH )
	2 cổng giao tiếp I²S
	10 kênh ngõ ra điều chế độ rộng xung (PWM)
	SD card/SDIO/MMC host
	Ethernet MAC hỗ trợ chuẩn: DMA và IEEE 1588
	CAN bus 2.0
	IR (TX/RX)
2.3.3. Cảm biến tích hợp
	1 cảm biến Hall (cảm biến từ trường)
	1 cảm biến đo nhiệt độ
	Cảm biến chạm (điện dung) với 10 đầu vào khác nhau.
2.3.4. WiFi & Bluetooth
	Wi-Fi: 802.11 b/g/n/e/i
	Station Mode (STA): Kết nối với các hotspot
	Access Point Mode (Soft AP): ESP32 trở thành 1 hotspot
	STA-AP: cả 2 chế độ trên
	Bluetooth: v4.2 BR/EDR và BLE
Bluetooth và WiFi có thể hoạt động cùng lúc nhưng không thể vừa nhận gói tin Bluetooth và dữ liệu WiFi vì tuy có 2 core nhưng chung ăng-ten.
Việc chạy song song cùng lúc 2 chức năng tiêu tốn rất nhiều năng lượng.



2.3.5 Mức tiêu thụ của các thành phần
Dưới đây là mức tiêu thụ của một số thành phần tiêu thụ điện áp trên ESP32: 
Tên thành phần	Mức tiêu thụ tối thiểu	Mức tiêu thụ tối đa
CPU	~0.1mA	160mA
Chip WiFi	~0.2mA	70-80mA
Chip Bluetooth	~0.3mA	20-30mA
Clock và RTC	0.1mA	1mA
GPIO	~0.1mA	40mA
RAM	~	50mA
Flash	~	6mA
ADC/DAC	1	2mA
Bảng 4.2. Mức tiêu thụ điện áp trên một số thành phần
Ngoài ra, mức độ tiêu thụ tối thiểu và tối đa của một ESP32 phụ thuộc vào các yếu tố như tốc độ xung nhịp, chế độ hoạt động của các thành phần như Wi-Fi, Bluetooth, RAM, flash, ADC, DAC, GPIO, vv.
Tuy nhiên, thường thì mức tiêu thụ điện năng của ESP32 tối thiểu là khoảng 20 mA khi hoạt động ở tốc độ xung nhịp tối thiểu, và tối đa là khoảng 300 mA khi hoạt động ở tốc độ xung nhịp tối đa và các thành phần hoạt động ở chế độ tối đa.

 
2.4. Low Power Mode
Hình 2.3.2. Các chế độ ngủ trong ESP32
- Vấn đề năng lượng luôn là một vấn đề quan trọng. Và 1 điều hạn chế của ESP32 đó chính là tiêu tốn tương đối nhiều năng lượng. 
- Ở chế độ hoạt động, dòng chip yêu cầu là 240mA, nếu dùng cả Bluetooth và WiFi có thể lên tới 790mA
- Do đó, ESP32 có một số tính năng giúp tối ưu lượng năng lượng tiêu thụ, tương ứng với mục đích sử dụng. 
Chế độ ngủ trong ESP32 (NGR) bao gồm:
* Sleep mode: trạng thái tiết kiệm năng lượng khi không sử dụng. Năng lượng chỉ đủ cung cấp cho RAM để lưu dữ liệu
* Light sleep: Tắt hết WiFi, BLE, RAM và CPU được định mức clock, dòng tiêu thụ ~0.8mA
* Deep sleep: Tắt RAM, CPU và hầu hết các thiết bị ngoại vi. Chỉ bật một số phần của chip như bộ điều khiển RTC, ngoại vi RTC, RTC memory. Dòng tiêu thụ lúc này là 0.15mA
* Hibernation: Tắt tất cả mọi thứ ngoại trừ bộ đếm thời gian RTC và một số chân GPIO của RTC. Các chân này giúp đánh thức chip khỏi chế độ ngủ đông



2.5. Tại sao nên sử dụng ESP32
 Hiện nay có rất nhiều dòng vi xử lý hỗ trợ tính năng Low Power và Ultra Low Power nhưng nhóm em vẫn lựa chọn ESP32 là vi xử lý vì có nhiều ưu điểm vượt trội so với các hãng vi xử lý khác đồng giá.
Cụ thể như sau:

Thông số kỹ thuật	ESP32	Arduino Uno	STM32F103C8T6
Vi xử lý	2 nhân, tốc độ cao	1 nhân, tốc độ thấp	Đa dạng, từ 1 đến nhiều
Tốc độ xung nhịp	Lên đến 240 MHz	16 MHz	Đa dạng, từ 16 MHz trở lên
Bộ nhớ Flash	4 MB	32 KB	Đa dạng, từ 16 KB trở lên
Bộ nhớ RAM	520 KB	2 KB	Đa dạng, từ 2 KB trở lên
Wi-Fi tích hợp	Có	Không	Không
Bluetooth tích hợp	Có	Không	Không
Bảng 2.3.3. Bảng so sánh chức năng ESP32 với Arduino và STM32

Do đó, ESP32 vẫn có những ưu điểm trong lĩnh vực low power nhờ tiêu thụ năng lượng thấp, tốc độ xử lý ưu việt, chế độ sleep đa lõi và quản lý nguồn điện thông minh. Điều này làm cho nó trở thành một lựa chọn phù hợp cho các ứng dụng yêu cầu hiệu suất low power và sử dụng pin lâu dài.
2.6. Giới thiệu module cảm biến dòng ACS712













Hình 2.4. Module cảm ứng dòng ACS712-5A
ASC712 là một IC (Integrated Circuit) cảm biến dòng mà được sử dụng để đo lường dòng điện xoay chiều. Nó cung cấp một tín hiệu tương tự (analog) đầu ra, dựa trên mức độ dòng điện đang chảy qua nó.
ASC712 sử dụng nguyên lý của hiệu ứng Hall để đo lường dòng điện. Nó bao gồm một cảm biến Hall và một bộ khuếch đại tín hiệu, cho phép nó đo các dòng điện có giá trị từ vài đến hàng trăm Ampe.
Thông thường, đầu ra của ASC712 được hiển thị bằng một mức điện áp tương tự (analog) trong khoảng từ 0 đến 5V, phụ thuộc vào mức độ dòng điện được đo. Có thể sử dụng ADC (Analog-to-Digital Converter) để chuyển đổi tín hiệu đầu ra của ASC712 thành một giá trị số để dễ dàng xử lý bởi vi điều khiển hoặc các vi mạch khác.
Các ứng dụng của ASC712 bao gồm đo lường dòng điện trong các hệ thống điện tử, hệ thống điều khiển động cơ và các ứng dụng khác liên quan đến điện.
- Sử dụng tín hiệu Analog (tương tự), khi tín hiệu vào MCU sẽ qua bộ ADC (Analog to Digital Converter), do đó độ chính xác phụ thuộc vào số bits mà MCU dùng để mã hóa tín hiệu 
- Arduino dùng 10bits để mã hóa tín hiệu thì số lượng các mức khác nhau mà 10bits có thể tạo ra là 210 = 1024 giá trị tương đương với 5V điện áp. Như vậy độ chia điện áp nhỏ nhất mà MCU phân biệt được là 5/1024 = 0.0048V. 
Đối với ACS712 5A thì tương ứng 185mV với 1A thì độ chia nhỏ nhất của ADC của Arduino có thể đo được giá dòng điện là 0.026A
Với độ chia này, ASC712 có độ chính xác cao hơn nhiều các loại đồng hồ đo đa năng.
2.7 Pin Lipo-3,7V 2000mAh
 
Hình 2.5. Pin Lipo
- Pin Lipo là viết tắt của Lithium Polymer – Cấu tạo của pin Lipo là sử dụng chất điện phân Polumer khô. Pin Lipo có điện áp 3.7V và dung lượng 2000mAh (milliampere-hour). Đây là một pin phổ biến và được sử dụng rộng rãi trong các ứng dụng di động, điện tử và robot.
- ESP32 là một vi điều khiển IoT (Internet of Things) mạnh mẽ và linh hoạt, sử dụng công nghệ tiết kiệm năng lượng. Nó có khả năng hoạt động ở điện áp cung cấp từ 2.2V đến 3.6V. Do đó, pin Lipo-3.7V có điện áp phù hợp để cấp nguồn cho ESP32 mà không cần sử dụng mạch hạ áp.
- Dung lượng pin 2000mAh cung cấp một lượng năng lượng đáng kể để vận hành ESP32 trong thời gian dài. Tuy nhiên, tiêu thụ năng lượng của ESP32 phụ thuộc vào các yếu tố như cấu hình phần cứng, chế độ hoạt động và ứng dụng cụ thể. Vì vậy, thời gian hoạt động thực tế của ESP32 trên pin Lipo-3.7V 2000mAh có thể khác nhau và cần được kiểm tra và đo đạc trong ứng dụng cụ thể của chúng ta.
3. Mô tả thiết kế hệ thống
 
Hình 3. Sơ đồ thiết kế hệ thống
- Thiết kế nghiên cứu về tiết kiệm năng lượng trong hệ thống bao gồm ESP32 và timer wake up, external wake up có thể được thực hiện như sau:
- ESP32: Đây là một vi xử lý mạnh mẽ và đa chức năng, được sử dụng để điều khiển và quản lý các thiết bị trong hệ thống.
- Timer wake up, external wake up: Đây chính là các phương pháp đánh thức thiết bị từ chế độ ngủ
- Cách hoạt động: ESP32 sẽ sử dụng giao thức và phương pháp giao tiếp để gửi và nhận dữ liệu với timer wake up, external wake up. Cụ thể, ESP32 sẽ tạo và gửi các gói tin dữ liệu thông qua giao thức nRF24L01 tương ứng, và timer wake up, external wake up nhận và giải mã các gói tin dữ liệu để truyền tới các thiết bị khác.
Giao tiếp giữa ESP32 và timer wake up, external wake up:
- Phương pháp giao tiếp: ESP32 và timer wake up, external wake up có thể giao tiếp thông qua giao thức SPI (Serial Peripheral Interface) hoặc giao thức I2C (Inter-Integrated Circuit).
- Giao thức giao tiếp: Đối với giao thức SPI, ESP32 sẽ đóng vai trò là master (chủ) và timer wake up, external wake up sẽ đóng vai trò là slave (thụ động). ESP32 sẽ điều khiển truyền và nhận dữ liệu thông qua các chân SPI (MISO, MOSI, SCK, SS)
- Để giảm sự tiêu thụ năng lượng, ta có thể đặt các chân I/O không cần thiết vào chế độ đầu ra không hoạt động (output disabled).
- Các chân I/O không hoạt động không tiêu thụ năng lượng và giúp tiết kiệm năng lượng hơn trong quá trình light sleep.
- Để thiết lập chế độ này, ta cần sử dụng các hàm và API cung cấp bởi ESP32 development environment (ví dụ: Arduino IDE hoặc ESP-IDF).
Giải thích quá trình hoạt động của hệ thống: 
- Hệ thống sử dụng vi điều khiển ESP32, cấp nguồn cho ESP32 và các thiết bị khác, ESP32 điều khiển các thiết bị thông qua các relays
- Nhấn nút Reset để gọi ESP32 thức dậy thực hiện công việc 
- ESP32 sẽ tự động đi vào chế độ ngủ sau 30s nếu không có bất kì hoạt động nào diễn ra

3.1. Tối ưu hóa chương trình và dữ liệu:
Để đạt được tiết kiệm năng lượng tối đa trong chế độ light sleep, ta cần tối ưu hóa chương trình và dữ liệu.
Loại bỏ những phần không cần thiết và không sử dụng trong chương trình.
Kiểm tra và tối ưu hóa các quy trình xử lý dữ liệu để giảm tần suất hoạt động của vi xử lý và tiêu thụ năng lượng.
Sử dụng các thuật toán và phương pháp tối ưu để giảm thiểu thời gian hoạt động của vi xử lý và các hoạt động không cần thiết khác trong quá trình light sleep.


4. Phương pháp thực hiện (Methodology):
4.1. Cài đặt phần cứng và firmware:
4.1.1. Cài đặt Hardware:
Kết nối ESP32 với timer wake up, external wake up thông qua các chân giao tiếp SPI (MISO, MOSI, SCK, CE, CSN, IRQ).
Đảm bảo kết nối điện và độc lập nguồn điện cho ESP32 và module.
4.1.2. Cài đặt Firmware:
Sử dụng môi trường phát triển ESP32 (ví dụ: Arduino IDE hoặc ESP-IDF) để viết và biên dịch firmware cho ESP32.
Triển khai mã firmware lên ESP32 để điều khiển các chức năng của hệ thống.
Đảm bảo firmware được cài đặt đúng và hoạt động chính xác với ESP32 
4.1.2.1. Các chế độ đánh thức của ESP32
Để chuyển từ chế độ NGR (Deep Sleep) sang chế độ đánh thức (wake), chúng ta có thể sử dụng các chế độ sau đây:
	Chế độ ngắt: Trong chế độ này, chúng ta sẽ thiết lập một thời gian ngắn cho việc đánh thức ESP32 và sau đó nó sẽ quay trở lại chế độ NGR. Để thiết lập chế độ ngắt, chúng ta có thể sử dụng hàm esp_sleep_enable_timer_wakeup() để đặt thời gian ngắt và sau đó gọi hàm esp_deep_sleep_start() để chuyển đổi sang chế độ NGR. Ví dụ:
	Chế độ đánh thức từ GPIO: Chúng ta có thể đặt ESP32 để đánh thức từ tín hiệu trên các chân GPIO nhất định. Để làm điều này, sử dụng hàm esp_sleep_enable_ext0_wakeup() để đặt GPIO và cấp cách nguồn cho tín hiệu đánh thức. Sau đó, gọi esp_deep_sleep_start() để chuyển đổi sang chế độ NGR. Ví dụ:
	Trong chế độ đánh thức từ chế độ ULP (Ultra Low Power) Chế độ đánh thức từ hẹn giờ RTC (Real-Time Clock): ESP32 có một RTC tích hợp để duy trì thời gian thực. Chúng ta có thể sử dụng chế độ đánh thức từ hẹn giờ RTC bằng cách sử dụng hàm esp_sleep_enable_timer_wakeup() và hàm esp_sleep_enable_timer_wakeup().
4.2. Thực hiện thí nghiệm:
4.2.1 Xác định mục tiêu thí nghiệm:
Xác định mục tiêu đo lường và đánh giá hiệu suất tiết kiệm năng lượng của hệ thống.
Ví dụ: Đo lường lượng năng lượng tiêu thụ trong chế độ hoạt động thường và chế độ light sleep để so sánh.
4.2.2 Thiết lập và thực hiện thí nghiệm:
Thiết lập các điều kiện và môi trường thí nghiệm như đo lường năng lượng, ghi lại dữ liệu, và điều khiển các tham số cần thiết.
Đo lường và ghi lại lượng năng lượng tiêu thụ của hệ thống trong các điều kiện hoạt động khác nhau, bao gồm chế độ hoạt động thường và chế độ light sleep.
Ghi lại các thông số và dữ liệu liên quan đến tiết kiệm năng lượng, như thời gian ngủ, tiêu thụ điện năng, và các thông số khác liên quan đến hiệu suất.








4.3 Đánh giá và phân tích kết quả:
Phân tích và so sánh dữ liệu thu thập được từ các điều kiện thí nghiệm khác nhau.
Đánh giá hiệu suất tiết kiệm năng lượng của hệ thống khi áp dụng chế độ light sleep.
Đưa ra nhận xét và kết luận về hiệu quả của việc sử dụng chế độ light sleep để tiết kiệm năng lượng trong hệ thống.
- Ở trạng thái full-active ESP32 tiêu thụ mức điện áp 80~85mA
- 1 Pin 18650-3,7V 2000mAh
Ta có công thức tính thời gian như sau:
Tổng thời gian hoạt động liên tục =(Dung lượng pin)/(Mức tiêu thụ )

Tổng thời gian hoạt động liên tục =2000/(85 )=23.52(h)
Ở trạng thái light-sleep ESP32 tiêu thụ mức điện áp 0.8mA:
Ta có công thức tính thời gian như sau:
Tổng thời gian hoạt động liên tục =(Dung lượng pin)/(Mức tiêu thụ )

Tổng thời gian hoạt động liên tục =2000/0.8=2500(h)
- Tính toán với giả thiết: 
Ứng dụng vào đời sống chúng ta có gia thiết:
- 1 gia đình 5 người mỗi ngày cần sử dụng thiết bị 20 lần, mỗi lần sử dụng 30s (0,0083h)
- Vậy theo công thức ta có:
Thời gian hoạt động  =Dòng tiêu thụ* thời gian tiêu thụ=20*85*0,0083(h)=14.11 mAh 
- Thời gian lâu nhất mà thiết bị có thể hoạt động
Tổng thời gian hoạt động liên tục =2000/14.11=141.74(h)
141,71~6 ngày 
- Vậy trong vòng 6 ngày cần sạc lại 1 lần
4.3.1. Phân tích và diễn giải kết quả:
Kết quả từ thí nghiệm đã cho thấy rằng việc áp dụng chế độ light sleep trên hệ thống ESP32 và timer wake up, external wake up đạt được hiệu suất tiết kiệm năng lượng đáng kể. Đây là một kết quả quan trọng và mang ý nghĩa trong việc thiết kế các hệ thống IoT hoạt động liên tục và cần tiết kiệm năng lượng.
Khi so sánh với các nghiên cứu liên quan, kết quả của thí nghiệm này có thể xác nhận rằng chế độ light sleep là một phương pháp hiệu quả để giảm tiêu thụ năng lượng trong các hệ thống IoT. Các nghiên cứu trước đây cũng đã chứng minh rằng việc tắt các thành phần không cần thiết và giảm tần suất hoạt động của vi xử lý trong chế độ light sleep có thể đem lại sự tiết kiệm năng lượng đáng kể.
Ý nghĩa của kết quả đối với thiết kế tiết kiệm năng lượng là rất lớn. Khi xây dựng các hệ thống IoT, tiết kiệm năng lượng là một yếu tố quan trọng để tăng tuổi thọ pin và giảm chi phí vận hành. Chế độ light sleep cung cấp một phương pháp đơn giản và hiệu quả để đạt được mục tiêu này. Kết quả của thí nghiệm này cho thấy rằng việc áp dụng chế độ light sleep có thể giúp gia tăng thời gian hoạt động của hệ thống IoT và giảm nhu cầu thay thế pin.




4.3.2. Đánh giá hạn chế:
Trong quá trình nghiên cứu, có một số hạn chế mà cần được đề cập và xem xét để cải thiện kết quả:
Hạn chế của môi trường thực tế: Thí nghiệm được thực hiện trong điều kiện mô phỏng và không gian giới hạn. Các yếu tố môi trường thực tế như tín hiệu nhiễu, khoảng cách truyền thông, và sự can thiệp từ các thiết bị khác có thể ảnh hưởng đến hiệu suất thực tế của hệ thống. Do đó, cần tiến hành thí nghiệm thêm trong các môi trường thực tế để đánh giá hiệu suất năng lượng trong điều kiện thực tế hơn.\
Hạn chế về độ tin cậy: Trong quá trình thí nghiệm, có thể gặp phải các sự cố kết nối không đáng kể hoặc mất mát dữ liệu khi sử dụng timer wake up, external wake up. Điều này có thể ảnh hưởng đến tính chính xác và độ tin cậy của hệ thống. Để cải thiện độ tin cậy, có thể xem xét sử dụng các giao thức và phương pháp bảo mật dữ liệu bổ sung.
Giới hạn của phần cứng và firmware: Hiệu suất tiết kiệm năng lượng của hệ thống phụ thuộc vào phần cứng và firmware được sử dụng. Nếu phần cứng không hỗ trợ chế độ light sleep hoặc có hạn chế về khả năng tiết kiệm năng lượng, kết quả có thể bị giới hạn. Đồng thời, firmware cũng cần được tối ưu hóa để đảm bảo tiêu thụ năng lượng thấp nhất trong quá trình light sleep. Tiến hành nghiên cứu và phát triển phần cứng và firmware tối ưu hơn có thể cải thiện hiệu suất tiết kiệm năng lượng của hệ thống.


5. Hướng phát triển tiếp theo:
- Dựa trên kết quả và hạn chế của nghiên cứu, có một số hướng phát triển tiếp theo mà có thể xem xét.
- Nghiên cứu về chế độ deep sleep: Xem xét áp dụng chế độ deep sleep để đánh giá hiệu suất tiết kiệm năng lượng trong điều kiện yêu cầu hoạt động của hệ thống cho phép. So sánh và phân tích hiệu suất giữa chế độ light sleep và deep sleep để tìm ra phương pháp tiết kiệm năng lượng tối ưu nhất cho ứng dụng cụ thể.
- Đánh giá hiệu suất thực tế: Tiến hành thí nghiệm và đánh giá hiệu suất tiết kiệm năng lượng trong các môi trường thực tế và điều kiện hoạt động khác nhau. Xem xét yếu tố như tín hiệu nhiễu, khoảng cách truyền thông, và sự can thiệp từ các thiết bị khác để đánh giá hiệu suất và độ tin cậy của hệ thống.
- Tối ưu hóa quản lý nguồn điện: Nghiên cứu và áp dụng các phương pháp quản lý nguồn điện tiên tiến để tăng hiệu suất tiết kiệm năng lượng của hệ thống. Các phương pháp như quản lý năng lượng động, dự đoán nhu cầu năng lượng, và điều chỉnh thông số cấu hình để tối ưu hóa việc sử dụng nguồn điện có thể được khám phá. Điều này có thể bao gồm việc sử dụng các chip quản lý nguồn điện tiết kiệm năng lượng hoặc thiết kế các mạch điện thông minh để giảm tiêu thụ năng lượng không cần thiết.
-Mở rộng phạm vi nghiên cứu: Nghiên cứu có thể mở rộng để xem xét hiệu suất tiết kiệm năng lượng trong các hệ thống IoT lớn hơn và phức tạp hơn. Các yếu tố như mạng lưới cảm biến, tích hợp nhiều module, và quản lý dữ liệu có thể được nghiên cứu để đảm bảo tiết kiệm năng lượng toàn diện và hiệu quả.
- Đánh giá khả năng mở rộng và tích hợp: Xem xét khả năng mở rộng và tích hợp của hệ thống tiết kiệm năng lượng. Nghiên cứu các phương pháp và giao thức giao tiếp để kết nối với các thiết bị và hệ thống khác trong môi trường IoT. Điều này có thể bao gồm việc sử dụng giao thức mạng tiết kiệm năng lượng, cơ chế quản lý đa thiết bị, và tích hợp với các hệ thống quản lý thông minh.
Các hướng phát triển này sẽ giúp cải thiện và mở rộng khả năng tiết kiệm năng lượng của hệ thống, đồng thời tạo ra các giải pháp tiết kiệm năng lượng thông minh cho các ứng dụng IoT trong tương lai.
- Từ nghiên cứu trên chúng ta có thể tích hợp mô hình trên vào mô hình khóa cửa sử dụng, vân tay

6. Thảo luận
- Ngoài công thức rút ra ở mục trên, chúng ta có một số vấn đề như sau:
6.1. Sơ đồ xả của pin
- Dòng xả của pin không có mối quan hệ tuyến tính với thời gian. Thay vào đó, dòng xả của pin thường tuân theo một đường cong không tuyến tính.
 
Hình 8.1: Sơ đồ quá trình sạc xả của pin
- Ban đầu, khi pin đầy đủ năng lượng, dòng xả thường ở mức thấp. Khi pin dùng điện năng để cung cấp cho các thiết bị hoặc ứng dụng, dòng xả tăng lên. Tuy nhiên, khi lượng năng lượng trong pin giảm, dòng xả không tăng theo một tốc độ tuyến tính, mà thường có xu hướng giảm dần theo thời gian.

Điều này được thể hiện trong khái niệm "độ suy giảm của pin" (battery discharge curve) mà mỗi loại pin có. Đường cong suy giảm này thường có dạng không tuyến tính và phụ thuộc vào nhiều yếu tố như công nghệ pin, dung lượng, cường độ dòng xả, và điều kiện sử dụng.
6.2. Độ suy hao pin

- Pin LiPo (Lithium Polymer) là một công nghệ pin phổ biến trong các thiết bị di động, drone, máy ảnh và các ứng dụng điện tử khác. Pin LiPo có nhiều ưu điểm như khối lượng nhẹ, kích thước mỏng, và khả năng cung cấp dòng điện cao.
Tuy nhiên, độ suy hao của pin LiPo không thể coi là không đáng kể. Như các loại pin lithium-ion khác, pin LiPo cũng có một số yếu tố ảnh hưởng đến tuổi thọ và hiệu suất sử dụng của nó.
Dưới đây là một số yếu tố có thể gây suy hao pin LiPo:
	Chu kỳ sạc-điều khiển: Pin LiPo có số lần chu kỳ sạc-điều khiển giới hạn. Mỗi lần sạc và xả đếm là một chu kỳ, và sau một số chu kỳ nhất định, hiệu suất pin sẽ giảm dần.
	Quá tải và quá xả: Quá tải pin (điện áp quá cao) hoặc quá xả pin (điện áp quá thấp) có thể gây suy hao và rủi ro cho pin LiPo.
	Nhiệt độ: Nhiệt độ quá cao hoặc quá thấp có thể ảnh hưởng đến hiệu suất và tuổi thọ của pin LiPo.
	Lưu trữ và bảo quản: Pin LiPo cần được lưu trữ và bảo quản đúng cách để tránh suy hao không cần thiết. Điều này bao gồm việc giữ pin ở mức điện áp an toàn và tránh tiếp xúc với điện tử kim loại.

7. Kết luận (Conclusion)
	Các kết quả chính đã đạt được từ nghiên cứu bao gồm: 
	Tiết kiệm năng lượng: Nghiên cứu đã chỉ ra rằng việc sử dụng chế độ light sleep trên ESP32 và timer wake up, external wake up có thể giúp giảm tiêu thụ điện năng một cách đáng kể. Điều này giúp tiết kiệm năng lượng và gia tăng tuổi thọ pin.
	Hiệu quả truyền thông: Sử dụng timer wake up, external wake up kết hợp với chế độ light sleep trên ESP32 giúp tăng hiệu quả truyền thông một cách đáng kể. Điều này giúp tăng cường khả năng kết nối và truyền tải dữ liệu cho các ứng dụng IoT
	Thời gian hoạt động kéo dài: Khi sử dụng chế độ light sleep, ESP32 và timer wake up, external wake up có thể hoạt động trong thời gian dài hơn mà vẫn tiết kiệm năng lượng.
	Cải thiện tính di động: Khi sử dụng chế độ light sleep, ESP32 và timer wake up, external wake up trở nên linh hoạt hơn khi không cần kết nối nguồn liên tục giúp tăng tính di động cho sản phẩm
	Sử dụng đơn giản: ESP32 và timer wake up, external wake up khi sử dụng chế độ light sleep, chỉ cần sử dụng các lệnh tương ứng và cấu hình thiết lập cần thiết để sử dụng trong các thiết kế mạch điện tử
	Tóm lại, các kết quả chính đã đạt được từ nghiên cứ chế độ light sleep sử dụng ESP32 và timer wake up, external wake up bao gồm tiết kiệm năng lượng, hiệu quả truyền thông, thời gian hoạt động kéo dài, tăng tính di động và sử dụng đơn giản. Các kết quả này cung cấp các cơ sở để áp dụng chế độ light sleep trong các thiết kế điện tử, giúp tiết kiệm năng lượng, tối ưu hóa hiệu suất và tăng tính di động cho các ứng dụng IoT.
	Ý nghĩa nghiên cứu: Nghiên cứu áp dụng chế độ light sleep trên hệ thống ESP32 và timer wake up, external wake up trong thiết kế tiết kiệm năng lượng có ý nghĩa và đóng góp đáng kể cho lĩnh vực này. 
	Tiết kiệm năng lượng: Chế độ light sleep giúp giảm tiêu thụ điện năng lượng một cách đáng kể trong các thiết bị điện tử. Điều này giúp tăng tuổi thọ pin, giảm chi phí điện và giảm thiểu sự lãng phí tài nguyên.
	Hiệu suất tối ưu: Chế độ light sleep cung cấp cách thức tối ưu hóa hiệu suất năng lượng cho các thiết bị điện tử. Việc sử dụng chế độ này giúp tối ưu hóa hiệu suất trong khi vẫn tiết kiệm năng lượng đáng kể.
	Tăng tính di động: Giảm sự phụ thuộc vào nguồn cung cấp năng lượng và đẩy cao tính di động của sản phẩm điện tử. Điều này giúp thúc đẩy tương tác giữa thiết bị và người dùng và tăng tính cạnh tranh trên thị trường.
	Giảm thiểu sự lãng phí tài nguyên: Sử dụng chế độ light sleep giúp giảm thiểu sử lãng phí tài nguyên và tài nguyên năng lượng. Điều này giúp bảo vệ môi trường và giúp bảo vệ quyền lợi của người sử dụng.
	Sự kết hợp với IoT: Chế độ light sleep được sử dụng rộng rãi trong các thiết bị IoT, giúp tối ưu hóa kết nối mạng và tối ưu hóa việc truyền tải dữ liệu trong đó, cải thiện tính linh hoạt và tính di động cho các thiết bị IoT.
	Tổng quan lại, các hướng phát triển này sẽ giúp cải thiện và mở rộng khả năng tiết kiệm năng lượng của hệ thống, đồng thời tạo ra các giải pháp tiết kiệm năng lượng thông minh cho các ứng dụng IoT trong tương lai.
