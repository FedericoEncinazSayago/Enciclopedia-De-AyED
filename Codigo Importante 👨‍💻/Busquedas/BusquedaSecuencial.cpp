int secuencial(int vector[],unsigned dimension,int datoBuscado)
{
    unsigned i = 0;

    while (i < dimension && vector[i] != datoBuscado)
    {
        i++;
    }
    
    if (i == dimension)
    {
        return -1;
    }
    else
    {
        return i;
    }
}