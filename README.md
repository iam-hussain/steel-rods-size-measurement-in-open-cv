Steel-Rod-Sizes-Measurement_OpenCV_C-Plus-Plus

This is the Project of Rod Size Measurement (Mainly for Steel Rod) with some Reference Number ( Pixel * Reference = mm ) 

Camera Used     :       U3V Series USB3.0 Industrial Camera:

Cam Model       :       U3VT132M-H 

USB             :       3.0 

Website         :       Www.do3think.Com 

Company         :       DO3THINK 

Made            :       China 

Focal Length    :       50 MM

Minimum Focus Distance = around 46.5 Cm 

Display Height 5 Cm = Around 63 Cm 

Better Result = 100 Cm to 240 Cm

Reference: 

Reference Number = Known Object Size in MM / Known Object Size in Pixel 

*Reference changes for Different distance and Different Lens

Example: At 300 Cm Distance Between Cam and Object Reference = 105 / 434 = 0.24193548

Distance between Object and Camera:

Finding the Distance between Object and Cam by 2 Object Variation in Pixel with Known m.

Where, 

a = Object a Size in Pixel 

b = Object b Size in Pixel 

m = Movement Distance in Cm 

d = Distance between Object and Cam

Therefore: Distance between Object and Cam (d) = m / (1-(a/b)) = m / ((b-a)/b)

Link: https://www.youtube.com/watch?v=Qm7vunJAtKY  

Object Size by Distance: 

Finding a real height of the Object with some constant input. Where, 

RH = Real Height of the Object 

OS = Object height in Screen is Pixel convert into MM 

SH = CMOS sensor Height in MM 

D = Distance between Object and Camera 

F = Focal Length 

H = Screen Height is Pixel

We Know that, Distance between Object and Camera (D) = (FRHH) / (OS*SH)

So we change into Real Height of the Object (RH) = (OSSHD) / (F*H)
