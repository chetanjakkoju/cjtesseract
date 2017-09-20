from cjtesseract import cjtesseract
import os

obj = cjtesseract()
os.system( "wget http://jeroen.github.io/images/testocr.png -O /tmp/test.png" )
print (obj.run_cjtesseract("/tmp/test.png"))
