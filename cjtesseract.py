from ctypes import cdll
import cv2
import sys
import time
import ctypes as ct_che
from cStringIO import StringIO
import collections
import operator
import uuid,os
try:
	import Image;
except:
	from PIL import Image

lib = cdll.LoadLibrary('./libcjtesseract.so')

class cjtesseract(object):
	def __init__(self):
		self.obj = lib.cjtesseract_new();
	def run_cjtesseract(self,image_filename):
		tempImageFileName = "/tmp/"+str( uuid.uuid4() )+".bmp"
		image = Image.open( image_filename );
		image.save( tempImageFileName );

		tempFileName = "/tmp/"+str( uuid.uuid4() )
		lib.Run_cjtesseract( self.obj, tempImageFileName , tempFileName)
		returnList = [];
		for line in open(tempFileName,"r"):
			sp = line.split("_cjseparator_");
			returnList.append( [sp[0], float(sp[1])] );
		try:
			os.remove( tempFileName );
			os.remove( tempImageFileName );
		except:
			pass;
			
		return returnList;
