/**
 *
 */
std::string encrypt(std::string m) {
	int count,keycount = 0;
	std::string key = "banking";
	for(auto i : m) {
		if(keycount == 7)
			keycount = 0;
		m[count] = i+key[keycount];
		while(m[count] < 33) {
			m[count]+=93;
		}
		while(m[count] > 126) {
			m[count]-=93;
		}
		count++;
	}
}