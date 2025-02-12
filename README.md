# KeyFeaturesOfLinux

Bài 1: So sánh Monolithic Kernel và Microkernel

Monolithic Kernel:

Hạt nhân nguyên khối được triển khai hoàn toàn dưới dạng một process nhất chạy trong một không gian địa chỉ duy nhất. Do đó, các hạt nhân như vậy thường tồn tại trên đĩa dưới dạng các tệp nhị phân tĩnh duy nhất. Tất cả các dịch vụ hạt nhân đều tồn tại và thực thi trong không gian địa chỉ hạt nhân lớn.

Việc giao tiếp trong hạt nhân rất đơn giản vì mọi thứ đều chạy ở chế độ hạt nhân trong cùng một không gian địa chỉ: Hạt nhân có thể gọi trực tiếp các hàm, như một ứng dụng không gian người dùng có thể làm. Ở đây, giao tiếp nhanh hơn do không có chi phí chuyển ngữ cảnh giữa các không gian bộ nhớ.

Microkernel:

Microkernel không được triển khai như một process lớn duy nhất. Thay vào đó, chức năng của hạt nhân được chia thành các quy trình riêng biệt, thường được gọi là máy chủ.

Chỉ những máy chủ thực sự yêu cầu các khả năng như vậy mới chạy ở chế độ thực thi đặc quyền. Các máy chủ còn lại chạy trong không gian người dùng và tách biệt nhau trong các không gian địa chỉ khác nhau.

Việc giao tiếp giữa các thành phần trong hạt nhân vi mô được thực hiện qua cơ chế truyền tin nhắn (IPC - Inter-Process Communication) thay vì gọi hàm trực tiếp.

Do sự phân tách rõ rắng, khi một máy chủ gặp lỗi, hệ thống không bị ảnh hưởng toàn bộ như hạt nhân nguyên khối.



So sánh ưu nhược điểm của hai mô hình này về hiệu suất, bảo trì, bảo mật.
# So sánh Hạt nhân Vi mô và Hạt nhân Đơn khối

| **Đặc điểm**     | **Hạt nhân Vi mô**         | **Hạt nhân Đơn khối**       |
|------------------|---------------------------|-----------------------------|
| **Kích cỡ**      | Nhỏ hơn                    | Lớn hơn, hệ điều hành và người dùng nằm trong cùng một không gian địa chỉ |
| **Thực hiện**    | Chậm hơn                    | Nhanh hơn                    |
| **Có thể mở rộng** | Dễ dàng mở rộng           | Phức tạp để mở rộng           |
| **Bảo vệ**       | Nếu dịch vụ bị sập, hệ thống vẫn hoạt động  | Nếu một tiến trình/dịch vụ bị sập, toàn bộ hệ thống có thể bị sập |
| **Ví dụ**        | L4Linux, macOS             | Windows, Linux, BSD         |
| **Bảo mật**      | An toàn hơn vì chỉ những dịch vụ thiết yếu chạy ở chế độ hạt nhân | Dễ bị tấn công do nhiều mã chạy ở chế độ hạt nhân |
| **Nền tảng độc lập** | Di động hơn, trình điều khiển chạy trong không gian người dùng | Ít di động hơn do truy cập phần cứng trực tiếp |
| **Giao tiếp**    | Truyền tin nhắn giữa các máy chủ không gian người dùng | Gọi hàm trực tiếp trong kernel |
| **Hiệu suất**    | Thấp hơn do chi phí truyền tin nhắn | Cao hơn nhờ gọi hàm trực tiếp và ít chi phí hơn |


Giải thích tại sao Linux sử dụng Monolithic Kernel nhưng vẫn có tính linh hoạt cao.

     +Nhân Linux cung cấp các mô-đun. Mô-đun là một tệp đối tượng có mã có thể được liên kết đến (và hủy liên kết khỏi) nhân khi chạy. Mã đối tượng thường bao gồm một tập hợp các hàm triển khai hệ thống tệp, trình điều khiển thiết bị hoặc các tính năng khác ở lớp trên cùng của nhân. Mô-đun, không giống như các lớp bên ngoài của hệ điều hành nhân vi mô-đun, không chạy 1 process khác. Thay vào đó, nó được thực thi ở Chế độ nhân 1 không gian chung(process chung), giống như bất kỳ hàm nhân nào được liên kết tĩnh khác. Những lợi thế chính của việc sử dụng mô-đun bao gồm: phương pháp mô-đun hóa Vì bất kỳ mô-đun nào cũng có thể được liên kết và hủy liên kết khi chạy, nên các lập trình viên hệ thống phải giới thiệu các giao diện phần mềm được xác định rõ ràng để truy cập các cấu trúc dữ liệu do mô-đun xử lý. Điều này giúp dễ dàng phát triển các mô-đun mới.


Bài 2: Mô hình "Everything as a File" trong Linux
        ◦ Đề bài:
            ▪ Giải thích mô hình "Everything as a File".
            ▪ Nêu các đối tượng trong Linux hoạt động như file (ví dụ: thiết bị, tiến trình).
            ▪ Chạy lệnh kiểm tra và phân tích đầu ra để chứng minh rằng Linux áp dụng mô hình này.
      Hướng dẫn làm:Giải thích mô hình:
          
            ▪ Định nghĩa “Everything as a File” và lợi ích của nó.
            ▪ Định nghĩa “Everything as a File”
"Everything as a File" (Mọi thứ là tệp) là một nguyên tắc thiết kế trong hệ điều hành, đặc biệt phổ biến trong các hệ điều hành kiểu Unix (Linux, macOS). Theo nguyên tắc này, hầu hết mọi tài nguyên hệ thống đều được thể hiện dưới dạng tệp, bao gồm:

    • Tệp dữ liệu (text files, binary files)
    • Thư mục (directories, cũng được coi là tệp đặc biệt)
    • Thiết bị phần cứng (ổ đĩa, bàn phím, chuột, màn hình, cổng mạng)
    • Tiến trình và luồng (process descriptor )
    • Giao diện hệ thống (socket descriptore, pipe,  như /proc và /sys trong Linux)
Ví dụ, trên Linux, bàn phím có thể được truy cập qua tệp /dev/input/eventX, còn thông tin về CPU có thể đọc từ /proc/cpuinfo.

Lợi ích của “Everything as a File”

    1. Đơn giản hóa mô hình hệ thống
        ◦ Không cần nhiều API phức tạp để quản lý các loại tài nguyên khác nhau.
        ◦ Có thể thao tác với thiết bị như thao tác với tệp: mở (open), đọc (read), ghi (write), đóng (close).
    2. Dễ dàng lập trình và quản trị
        ◦ Các ứng dụng có thể sử dụng các thao tác tệp chuẩn thay vì phải viết mã đặc biệt cho từng loại thiết bị.
        ◦ Các lệnh Unix (cat, echo, grep, sed, ...) có thể làm việc với thiết bị giống như với tệp thông thường.
    3. Tăng khả năng tương thích và mở rộng
        ◦ Bất kỳ tài nguyên nào có thể được trừu tượng hóa thành tệp mà không cần thay đổi ứng dụng.
        ◦ Cho phép giao tiếp giữa các tiến trình (IPC) bằng cách đọc/ghi vào các tệp hoặc pipe.
    4. Bảo mật tốt hơn
        ◦ Hệ thống quyền truy cập tệp (permission) của Unix có thể được áp dụng đồng bộ cho tất cả tài nguyên.
        ◦ Giới hạn quyền truy cập vào thiết bị chỉ qua hệ thống tệp giúp kiểm soát bảo mật tốt hơn.

Tóm lại, nguyên tắc "Everything as a File" giúp hệ thống đơn giản, nhất quán, dễ quản lý và mở rộng.
              
        ◦ Thực hành:
            ▪ Dùng các lệnh ls -l /dev, cat /proc/cpuinfo, echo "Test" > /dev/null để kiểm tra.

            Bài 3: Cách Linux thực hiện Preemptive Multitasking
Đề bài:
Giải thích Preemptive Multitasking là gì.
Mô tả vai trò của Linux Scheduler trong việc quản lý tiến trình.
Hướng dẫn làm:
Giải thích:
Vai trò của Scheduler:

  +Bộ lập lịch quy trình(scheduler) là hệ thống con của hạt nhân phân chia tài nguyên hữu hạn của thời gian xử lý cho các quy trình của hệ thống. Nói cách khác, bộ lập lịch quy trình (hay đơn giản là
bộ lập lịch) là thành phần của hạt nhân chọn quy trình nào để chạy tiếp theo. Khi quyết định quy trình nào có thể chạy và khi nào, bộ lập lịch có trách nhiệm tối đa hóa việc sử dụng bộ xử lý đồng thời tạo ra ảo giác rằng nhiều quy trình đang thực thi đồng thời và liền mạch.


Phân biệt Preemptive Multitasking và Cooperative Multitasking.

 Preemptive Multitasking:
 
  + Scheduler quyết định khi nào một process sẽ gừng chạy và process mới sẽ bắt đầu chạy. 
Hành động vô tình tạm dừng một  đang chạy được gọi là ưu tiên. Thời gian một quy trình chạy
trước khi bị ưu tiên thường được xác định trước và được gọi là lát cắt thời gian(slice) của quy trình.
Trên thực tế, lát cắt thời gian cung cấp cho mỗi q trình có thể chạy một 1  phần thời gian của bộ xử lý. Việc quản lý lát cắt thời gian cho phép trình lập lịch đưa ra quyết định lập lịch toàn cục cho hệ thống. Nó cũng ngăn không cho bất kỳ quy trình nào độc quyền bộ xử lý. 

Cooperative Multitasking:

     + Ngược lại, trong đa nhiệm hợp tác, một quy trình không dừng chạy cho đến khi nó tự nguyện quyết định làm như vậy. Hành động của một quy trình tự nguyện tạm dừng chính nó được gọi là nhường(yielding). Lý tưởng nhất là, các quy trình thường nhường, cung cấp cho mỗi quy trình có thể chạy một phần bộ xử lý , nhưng hệ điều hành không thể quyết  điều này. Những thiếu sót của phương pháp này rất rõ ràng: scheduler không thể đưa ra quyết định toàn cầu về thời gian chạy của các quy trình; các quy trình có thể độc quyền bộ xử lý lâu hơn mong muốn của người dùng; và một quy trình bị treo không bao giờ nhường có khả năng làm sập toàn bộ hệ thống. 


Mô tả thuật toán Completely Fair Scheduler (CFS) và các yếu tố quyết định scheduling.
Ý tưởng đằng sau CFS – 

    • Mỗi tiến trình có thể chạy đều có thời gian ảo liên kết với nó trong PCB (khối điều khiển tiến trình).
    
    • Bất cứ khi nào có sự chuyển đổi ngữ cảnh xảy ra (hoặc tại mọi điểm lập lịch) thì thời gian ảo của tiến trình đang chạy hiện tại sẽ tăng lên virtualruntime_currprocess+=T. trong đó T là thời gian mà tiến trình được thực thi gần đây.
    
    • Biến vruntime lưu trữ thời gian chạy ảo của một tiến trình, đây là thời gian chạy thực tế (thời gian tiến trình đã chạy) được chuẩn hóa (hoặc điều chỉnh) theo số lượng tiến trình có thể chạy. Đơn vị của thời gian chạy ảo là nanosecond, do đó vruntime không phụ thuộc vào nhịp của bộ đếm thời gian (timer tick). Thời gian chạy ảo được sử dụng để giúp chúng ta mô phỏng một bộ xử lý đa nhiệm lý tưởng, mà Completely Fair Scheduler (CFS) đang cố gắng thực hiện.
    
    • Chọn tiến trình có thời gian chạy(vRuntime) ngắn nhất chạy tiếp.
    
    • Do đó, thời gian chạy của quy trình tăng dần theo chiều đơn điệu.
    
Vì vậy, ban đầu mỗi tiến trình đều có một thời gian ảo ban đầu
CFS là thuật toán khá đơn giản để lập lịch trình tiến trình và được triển khai bằng cách sử dụng Cây ĐỎ ĐEN chứ không phải hàng đợi. 
Vì vậy, tất cả các tiến trình nằm trong bộ nhớ chính được chèn vào Cây Đỏ Đen và bất cứ khi nào một tiến trình mới đến, nó sẽ được chèn vào cây. 




Thực hành kiểm chứng:
Dùng ps -eo pid,pri,ni,cmd kiểm tra mức ưu tiên của tiến trình.
