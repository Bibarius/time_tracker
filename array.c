#define INCREASE_NUMBER 5
int FreeCells = 0;
int OccupiedCells = 0;

typedef struct Element{
    char *name;
    int hours;
    int minutes;
    int seconds;
} Element;



Element *init_array(int size)
{
    Element *ptr;
    ptr = (Element*)malloc(size * sizeof(Element));
    FreeCells = size;

    int i;
    for(i = 0; i < size; i++)   ptr[i].name = NULL;


    return ptr;    
}

Element *copy(Element *array)
{    
    
    // Element *tmp; 
    // int i;
    // tmp = (Element*)malloc((OccupiedCells * sizeof(Element)) + (INCREASE_NUMBER * sizeof(Element)));
    // for(i = 0; i < OccupiedCells; i++)
    // {
    //     tmp[i].ID = array[i].ID;
    //     tmp[i].name = array[i].name;
    // }


    array = (Element*)realloc(array, (OccupiedCells * sizeof(Element)) + (INCREASE_NUMBER * sizeof(Element)));
    FreeCells += INCREASE_NUMBER; 

    return array;    
}

void add(Element new, Element *array)
{
    if(FreeCells == 0)  array = copy(array);

    array[OccupiedCells].name = new.name;
    array[OccupiedCells].hours = new.hours;
    array[OccupiedCells].minutes = new.minutes;
    array[OccupiedCells].seconds = new.seconds;
    OccupiedCells++;
    FreeCells--;
}