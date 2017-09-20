#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class cjtesseract {
	private:
  		tesseract::TessBaseAPI *api;
		bool isInit;
	public:
	cjtesseract() {
		api = new tesseract::TessBaseAPI();
		isInit = 0;
		if( api->Init(NULL, "eng") ) {
		      fprintf(stderr, "Could not initialize tesseract.\n");
		      exit(1);
		}
		isInit = 1;
	}
	void run_tesseract(char *img_filename, char * out_file  ){
		if( isInit == 0 ) {
		      fprintf(stderr, "Cannot run tesseract as it was initialized improperly");
			return;
		}

		  Pix *image = pixRead(img_filename);
		  api->SetPageSegMode(tesseract::PSM_AUTO_OSD);
		  api->SetVariable("tessedit_char_whitelist","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()=-_[]{}:;<>,./?|+");
		  api->SetImage(image);
		  api->Recognize(0);
		  tesseract::ResultIterator* ri = api->GetIterator();
		  tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
		  
		FILE * fp = fopen(out_file,"w");
		  if (ri != 0) {
		    do {
		      const char* word = ri->GetUTF8Text(level);
		      float conf = ri->Confidence(level);
		      int x1, y1, x2, y2;
		      ri->BoundingBox(level, &x1, &y1, &x2, &y2);
		      char tempstr[2048];
		      sprintf(tempstr, "%s_cjseparator_%.2f\n", word, conf );
		      fwrite(tempstr, strlen(tempstr), 1  , fp );
		//      printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
		//               word, conf, x1, y1, x2, y2);
		      delete[] word;
		    } while (ri->Next(level));
		  }
		fclose(fp);
	}
};

/*
int main() {
	cjtesseract obj;
	// "Always pass BMP or tiff file to this function"
	obj.run_tesseract("resume.bmp", "/tmp/1");
	return 0;
}
*/

extern "C" {
	cjtesseract * cjtesseract_new() { return new cjtesseract(); }
	void Run_cjtesseract( cjtesseract * foo, char * imagefilename, char *outfname) {
		foo->run_tesseract( imagefilename, outfname);
	}
}
