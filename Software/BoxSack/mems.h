
const int8_t AFS_SEL_2G = 0; 
const int8_t AFS_SEL_4G = 1; 
const int8_t AFS_SEL_8G = 2; 
const int8_t AFS_SEL_16G = 3; 

void setup_MPU_Power();

void setup_AFS_divider(int8_t afs_sel);
void setup_MPU_Acceleration(int8_t afs_sel);

void read_MPU_Acceleration(float& fax, float& fay, float& faz);

void high_pass_filter_xyz(float& fax, float& fay, float& faz);
float high_pass_filter(float filtered, float weight, float actual);
float low_pass_filter(float filtered, float weight, float actual);

float magnitude(float x, float y, float z);

