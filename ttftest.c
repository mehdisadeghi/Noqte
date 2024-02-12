#include <SDL.h>
#include <SDL_ttf.h>
#include <hb.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

void blit(SDL_Texture *texture, int x, int y, int rtl);
SDL_Texture *loadTXTTexture(char *text, TTF_Font *font, int rtl);

static TTF_Font *noqte;
static TTF_Font *dejavu;
static TTF_Font *noto;
static TTF_Font *console;
static TTF_Font *consolereg;
static SDL_Window *window; 
static SDL_Renderer *renderer;

int main(int argc, char* argv[])
{
	bool screenshot = false;
	if (argc > 1) {
		if(strcmp(argv[1], "-s") == 0) {
			screenshot = true;
		}
	}
	const int WIDTH = 1440;
	const int HEIGHT = 1024;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL_ttf");
		exit(1);
	}

	int major, minor, patch;
	TTF_GetHarfBuzzVersion(&major, &minor, &patch);
	if (!(major || minor || patch))
	{
		printf("SDL_ttf compiled without HarfBuz support");
		exit(1);
	}

	noqte = TTF_OpenFont("noqte.ttf", 50);
	if (noqte == NULL)
	{
		printf("Couldn't load the font");
		exit(1);
	}

	window = SDL_CreateWindow("ttftest",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		screenshot? SDL_WINDOW_HIDDEN: SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("Failed to open window: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	
	SDL_Texture *t01 = loadTXTTexture("ء ا آ ب پ ت ث ج چ ح خ د ذ ر ز ژ س ش", noqte, 1);
	SDL_Texture *t02 = loadTXTTexture("ص ض ط ظ ع غ ف ق ک گ ل م ن و ه ی ", noqte, 1);
	SDL_Texture *t03 = loadTXTTexture(
		"۱۲°۳۴۵۶۷۸۹۰!"
		"÷ ! ٬ ٫ ٪ ﷼ × ، * ) ( ـ + - = "
		, noqte, 1);
	SDL_Texture *t04 = loadTXTTexture(
		//"ْ  ٌ  ٍ  ً  ُ  ِ  َ  ّ  ٓ  ٔ "
		"ْ  ٌ  ٍ  ً  ُ  ِ  َ  ّ  ] [ } { » « : ;"
		" > < ؟ < . /"
		, noqte, 1);
	SDL_Texture *t05 = loadTXTTexture(
		"در صورت حذف این چند واژه غلط به شکیل، ثابت و جامع‌تر ساختن ",
		noqte, 1);
	SDL_Texture *t06 = loadTXTTexture(
		"پاراگراف شعر از لحاظ دوری از قافیه‌های اضافه کمک می‌شود.",
		noqte, 1);
	SDL_Texture *t07 = loadTXTTexture("äüößabcdefghijklmnñopqrstuvwxyz", noqte, 0);
	SDL_Texture *t08 = loadTXTTexture("ÄÜÖẞABCDEFGHIJKLMNÑOPQRSTUVWXYZ", noqte, 0);
	SDL_Texture *t09 = loadTXTTexture("~0123456789°!\"§$%&/()=?^<>*-;,’`´" , noqte, 0);
	
	SDL_Texture *t10 = loadTXTTexture("The quick brown fox jumps over the lazy dog.", noqte, 0);
	SDL_Texture *t11 = loadTXTTexture("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.", noqte, 0);
	SDL_Texture *t12 = loadTXTTexture("el veloz murciélago hindú comía feliz cardillo y kiwi.", noqte, 0);
	SDL_Texture *t13 = loadTXTTexture("la cigüeña tocaba el saxofón detrás del palenque de paja.", noqte, 0);
 

	SDL_Texture* fullTexture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

	SDL_Event event;

	while (1)
	{
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					exit(0);
					break;

				default:
					break;
			}
		}

		if (screenshot) {
			SDL_SetRenderTarget(renderer, fullTexture);

		}

		int right = WIDTH;

		blit(t01, right, 25, 1);
		blit(t02, right, 100, 1);
		blit(t03, right, 175, 1);
		blit(t04, right, 250, 1);

		blit(t05, right, 325, 1);
		blit(t06, right, 400, 1);

		blit(t07, 10, 475, 0);
		blit(t08, 10, 550, 0);

		blit(t09, 10, 625, 0);
		blit(t10, 10, 700, 0);
		blit(t11, 10, 775, 0);
		blit(t12, 10, 850, 0);
		blit(t13, 10, 925, 0);

		SDL_Delay(32);
		SDL_RenderPresent(renderer);

		if (screenshot) {
			// Reset the render target to the default window
			//SDL_SetRenderTarget(renderer, NULL);
			// Create a surface to store the contents of the fullTexture
			SDL_Surface* surface = SDL_CreateRGBSurface(
				0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
			// Copy the contents of the fullTexture to the surface
			SDL_RenderCopy(renderer, fullTexture, NULL, NULL);
			SDL_RenderReadPixels(
				renderer, NULL,
				SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
			// Save the surface as an image file
			IMG_SavePNG(surface, "glyphs.png");
			SDL_DestroyTexture(fullTexture);
			SDL_FreeSurface(surface);
			break;
		}
	}



	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(noqte);
	TTF_Quit();
	SDL_Quit();
}

SDL_Texture *loadTXTTexture(char *text, TTF_Font *font, int rtl)
{
	SDL_Rect dest;

	SDL_Color colorA = { 0xff, 0x99, 0x00, 0xff };

	if (rtl)
	{
		TTF_SetDirection(HB_DIRECTION_RTL);
		TTF_SetScript(HB_SCRIPT_ARABIC);
	} else {
		TTF_SetDirection(HB_DIRECTION_LTR);
		TTF_SetScript(HB_SCRIPT_LATIN);
	}

	SDL_Surface *surface;

	surface = TTF_RenderUTF8_Blended(font, text, colorA);

	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y, int rtl)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (rtl)
		dest.x -= dest.w;

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
