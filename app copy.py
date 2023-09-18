from flask import Flask
import qrcode
import io

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p> Fuck, World </p>"

# Method 1: Simple Method
img = qrcode.make("https://www.linkedin.com/in/rohit--kumar-/")
img.save("myfirst_file.png")

# showing the img of your QR code  
from skimage import io
img = io.imread("myfirst_file.png")
io.imshow(img)

# Create an Instance
qr = qrcode.QRCode(version=1,
error_correction=qrcode.constants.ERROR_CORRECT_M, 
box_size=10, border=4,)


# Add Data
qr.add_data("https://www.linkedin.com/in/rohit--kumar-/")
qr.make(fit=True)

# Save QR-code as image
img2 = qr.make_image(fill_color='black',back_color='red')
img2.save("mysecond_file.png")

# showing the img of your QR code  
from skimage import io
img = io.imread("mysecond_file.png")
io.imshow(img)

# How to Decode
import cv2 
detector= cv2.QRCodeDetector()

reval,point,s_qr = detector.detectAndDecode(cv2.imread('mysecond_file.png'))

# Decoded Text or Data
print(reval)

if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)