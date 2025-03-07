#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/ioctl.h>
using namespace std;

char lumchars[] = ".,-~:;=+*#%@"; // characters to display
float R1 = 1.0; // donut radius
float R2 = 0.4; // tube radius
float K2 = 6;   // donut distance from viewer
float tstep = 0.02;  // donut rotation step
float pstep = 0.005; // tube rotation step
float A = 0, B = 0; // donut rotation
bool safcol = true; // use terminal safe colors
float wb = 0; // donut rotation
int fps = 20; // frames per second

int main(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "--true")==0||strcmp(argv[i], "-t")==0) safcol = false;
        else if (strcmp(argv[i], "--safe")==0||strcmp(argv[i], "-s")==0) safcol = true;
        else if (strcmp(argv[i], "--fps")==0||strcmp(argv[i], "-f")==0) {
            if (i+1<argc) {
                fps = atoi(argv[i+1]);
                if (fps<=0) fps = 20;
                i++;
            }
        }
        else if (strcmp(argv[i], "--chars")==0||strcmp(argv[i], "-c")==0) {
            if (i+1<argc) {
                string chrs = argv[i+1];
                if (!chrs.empty()) {
                    string uchrs;
                    for (char c:chrs) if (uchrs.find(c) == string::npos) uchrs+=c;
                    strcpy(lumchars, uchrs.c_str());
                }
                i++;
            }
        }
        else if (strcmp(argv[i], "--help")==0||strcmp(argv[i], "-h")==0) cout<<"Usage: "<<argv[0]<<" [options]\n"<<"Options:\n"<<"  -t, --true    Use true RGB colors\n"<<"  -s, --safe    Use terminal safe colors (default)\n"<<"  -f, --fps N   Set animation speed to N frames per second (default: 20)\n"<<"  -c, --chars S Use characters in string S for rendering (duplicates removed)\n"<<"  -h, --help    Show this help message\n", exit(0);
    }
    cout<<"\x1b[2J";
    while(true) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int tw = w.ws_col;
        int th = w.ws_row-3;
        vector<vector<char>> res(th, vector<char>(tw, ' '));
        vector<vector<float>> zbuffer(th, vector<float>(tw, 0));
        vector<vector<int>> colors(th, vector<int>(tw, 0));
        float K1 = tw*K2*3/(8*(R1+R2));
        for(float t=0; t<2*M_PI; t+=tstep) {
            for(float p=0; p<2*M_PI; p+=pstep) {
                float cx = R1+R2*cos(p);
                float cy = R2*sin(p);
                float x = cx*(cos(B)*cos(t)+sin(A)*sin(B)*sin(t))-cy*cos(A)*sin(B);
                float y = cx*(sin(B)*cos(t)-sin(A)*cos(B)*sin(t))+cy*cos(A)*cos(B);
                float z = K2+cx*cos(A)*sin(t)+cy*sin(A);
                float ooz = 1/z;
                int xp = (int)(tw/2+K1*ooz*x);
                int yp = (int)(th/2-K1*ooz*y*0.5);
                float L = cos(p)*cos(t)*sin(B)-cos(A)*cos(t)*sin(p)-sin(A)*sin(t)+cos(B)*(cos(A)*sin(t)-cos(t)*sin(A)*sin(p));
                L = L*0.7+0.3;
                if(xp>=0&&xp<tw&&yp>=0&&yp<th&&ooz>zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;
                    int lumidx = (int)(L*12);
                    if(lumidx<0) lumidx = 0;
                    if(lumidx>strlen(lumchars)-1) lumidx = strlen(lumchars)-1;
                    res[yp][xp] = lumchars[lumidx];
                    int hue = (int)((t/M_PI+p/M_PI+A)*180)%360;
                    colors[yp][xp] = hue;
                }
            }
        }
        cout<<"\x1b[H";
        for(int y=0; y<th; y++) {
            for(int x=0; x<tw; x++) {
                if(res[y][x]!=' ') {
                    if(safcol) {
                        int hue = colors[y][x];
                        int colc;
                        if(hue<45) colc = 31;
                        else if(hue<90) colc = 33;
                        else if(hue<135) colc = 32;
                        else if(hue<180) colc = 36;
                        else if(hue<225) colc = 34;
                        else if(hue<270) colc = 35;
                        else if(hue<315) colc = 31;
                        else colc = 33;
                        float br = (strchr(lumchars, res[y][x])-lumchars)/strlen(lumchars)-1.0;
                        if(br>0.5) colc+=60;
                        printf("\x1b[%dm%c\x1b[0m", colc, res[y][x]);
                    } else {
                        int hue = colors[y][x];
                        int r, g, b;
                        if(hue<60) {r = 255; g = (hue*255)/60; b = 0;} 
                        else if(hue<120) {r = 255-((hue-60)*255)/60; g = 255; b = 0;} 
                        else if(hue<180) {r = 0; g = 255; b = ((hue-120)*255)/60;} 
                        else if(hue<240) {r = 0; g = 255-((hue-180)*255)/60; b = 255;} 
                        else if(hue<300) {r = ((hue-240)*255)/60; g = 0; b = 255;} 
                        else {r = 255; g = 0; b = 255-((hue-300)*255)/60;}
                        float br = 0.5+0.5*(strchr(lumchars, res[y][x])-lumchars)/strlen(lumchars)-1.0;
                        r = (int)(r*br);
                        g = (int)(g*br);
                        b = (int)(b*br);
                        printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", r, g, b, res[y][x]);
                    }
                } else putchar(' ');
            }
            putchar('\n');
        }
        printf("\x1b[%d;1H", th+1);
        printf("\x1b[37m╔");
        for(int i=0; i<tw-2; i++) printf("═");
        printf("╗\n╚");
        char st[100];
        sprintf(st, " 3D Donut | Rotation: A=%.2f, B=%.2f | Terminal: %dx%d ", A, B, tw, th);
        int stlen = strlen(st);
        int pad = (tw-2-stlen)/2;
        for(int i=0; i<pad; i++) printf("═");
        for(int i=0; i<stlen; i++) {
            int colc = 31+(i%7);
            printf("\x1b[%dm%c\x1b[0m", colc, st[i]);
        }
        for(int i=0; i<tw-2-pad-stlen; i++) printf("═");
        printf("╝\x1b[0m");
        A+=0.03;
        B+=0.015;
        wb+=0.03;
        if(sin(wb)>0) {
            A+=0.005*sin(wb);
            B-=0.004*sin(wb*1.3);
        }
        usleep(1000000/fps);
    }
    return 0;
}