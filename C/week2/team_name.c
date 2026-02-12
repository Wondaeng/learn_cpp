#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int is_lexicographically_smaller(char str1[], char str2[]) {
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] < str2[i]) return 1;
        if (str1[i] > str2[i]) return 0;
    }
}


int main(void) {
	char yeondu_name[21] = "";
	scanf("%s", yeondu_name);

	int num_team_names = 0;
	scanf("%d", &num_team_names);

	char team_name[21] = "";
	char best_team_name[21] = "";
	int score = 0;
	int best_score = 0;
	for (int i = 0; i < num_team_names; i++) {
		scanf("%s", team_name);
		
    	int count_l = 0;
    	int count_o = 0;
    	int count_v = 0;
    	int count_e = 0;
    
    	for (int j = 0; yeondu_name[j] != '\0'; j++) {
    		if (yeondu_name[j] == 'L') {
    			count_l += 1;
    		}
    		else if (yeondu_name[j] == 'O') {
    			count_o += 1;
    		}
    		else if (yeondu_name[j] == 'V') {
    			count_v += 1;
    		}
    		else if (yeondu_name[j] == 'E') {
    			count_e += 1;
    		}
    	}
    	
		for (int j = 0; team_name[j] != '\0'; j++) {
			if (team_name[j] == 'L') {
				count_l += 1;
			}
			else if (team_name[j] == 'O') {
				count_o += 1;
			}
			else if (team_name[j] == 'V') {
				count_v += 1;
			}
			else if (team_name[j] == 'E') {
				count_e += 1;
			}
		}
		/* ((L+O) × (L+V) × (L+E) × (O+V) × (O+E) × (V+E)) mod 100 */
		score = ((count_l + count_o) * (count_l + count_v) * (count_l + count_e) * 
			(count_o + count_v) * (count_o + count_e) * (count_v + count_e)) % 100;
		
		if (score > best_score) {
			best_score = score;
            
            int k = 0;
            for (k = 0; team_name[k] != '\0'; k++) {
                best_team_name[k] = team_name[k];
            }
            best_team_name[k] = '\0';
		} else if (score == best_score) {
		    if (is_lexicographically_smaller(team_name, best_team_name)) {
    			best_score = score;
                
                int k = 0;
                for (k = 0; team_name[k] != '\0'; k++) {
                    best_team_name[k] = team_name[k];
                }
                best_team_name[k] = '\0';		        
		    }
		}
	}
	printf("%s", best_team_name);
	return 0;
}
