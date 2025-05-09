if (make_thread && (right_bound - left > 10000))
{
    auto f = pool.push_task(quicksort, array, left, right_bound);
    quicksort(array, left_bound, right);
    f.wait();
}
else
{
    quicksort(array, left, right_bound);
    quicksort(array, left_bound, right);
}