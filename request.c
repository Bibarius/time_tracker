#include "array.c"




Element *find_by_name(char *name, Element *array)
{
    printf("\nstarting to find by name %s of occupied %d cells\n", name, OccupiedCells);

    int i;
    for(i = 0; i < OccupiedCells; i++)
    {
        printf("find_by_name loop [%d] ", i);
        if(array[i].name == name)
        {
            printf("Element found by find_by_name()\n");
            return &array[i];
        }
    }
    printf("\nElement was not found by find_by_name()\n");
}


void create_process(char *name, Element *array)
{
    Element temp;
    temp.name = name;
    temp.hours = 0;
    temp.minutes = 0;
    temp.seconds = 5;
    add(temp, array);
    printf("\nnew process added\n");
    return;
}


void increase_time(Element *process)
{
    if(process->seconds < 55)
    {
        process->seconds += 5;
    }
    else if(process->seconds >= 55)
    {
        process->seconds = 0;
        if(process->minutes < 59)
        {
            process->minutes++;
        }
        else if(process->minutes >= 59)
        {
            process->minutes = 0;
            process->hours++;
        }
    }

    printf("time has been increased\n");
}


void request(char *proc_name, Element *array)
{
    Element *temp;
    if(find_by_name(proc_name, array))
    {
        temp = find_by_name(proc_name, array);
        increase_time(temp);
    }
    else
    {
        create_process(proc_name, array);
    }
    
}

