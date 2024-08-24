int table[105];
string pattern;
string txt;

void Table(string substring){
    int i=0, j=1;
    while(j<substring.size()){
        if(substring[i]==substring[j]){
            i++;
            table[j]=i;
            j++;
        }else{
            if(i==0){
                table[j]=0;
                j++;
            } else
                i=table[i-1];

        }
    }
}

pair<int, int> kmp(string texto, string substring){
    int N=texto.size();
    int M=substring.size();
    int i=0;
    int j=0;
    while((N-i)>=(M-j)){
        if(texto[i]==substring[j]){
            i++;
            j++;
        }
        if(j==M){
            j=table[j-1];
            return {i-j, i-1}; // Substring encontrada de i-j até i-1
        } else if(i<N and texto[i]!=substring[j]){
            if(j==0) i++;
            else{
                j=table[j-1];
            }
        }
    }
    return {-1, -1}; // Substring não encontrada
}