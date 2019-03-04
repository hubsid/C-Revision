Press J to jump to the feed. Press question mark to learn the rest of the keyboard shortcuts
r/C_Programming
Search r/C_Programming
LOG IN
SIGN UP

User account menu
r/C_Programming
Posts


Join the discussion
BECOME A REDDITOR

10

Posted byu/rafaelement
3 years ago
realloc() fail; can't find cause.
I have this function here that opens a file and reads every line in a char* array. This array, result, is supposed to contain pointers to char arrays which contain the lines from the file. I need to realloc() so I can read in files with varying numbers of lines without wasting or having too little memory.

Here's the code:

char **readFile(char *filename) {
    char line[100];
    char **result = NULL;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Error opening %s.\n", filename);
        exit(2);
    }

    int i = 1;
    while(fgets(line, 100, fp) != NULL) {
        result = (char**) realloc(result, i);
        result[i - 1] = (char*) malloc(strlen(line));
        strcpy(result[i - 1], line);
        printf("%p\n", result);
        printf("%s\n", line);
        i++;
    }
    return result;
}
What happens: after a few successful iterations, realloc() fails with SIGABRT saying realloc(): invalid next size: 0x0000000000602240 ***.

Perhaps importantly, this message is always the same (numbers too) and happens after the same line in the file everytime.

"Portion" of the input file:

Mandelplätzchen mit Marmeladenfüllung

Hildabrötchen

Cantuccini mit Cranberries

schokonester

Shortbread-Finger

Schnelle Mandelmakronen

Vanillekipferl mit ungeschälten Mandeln

Echte Zimtsterne

fails right after reading schokonester, in the first line of the next while loop.

I hope you can help me with that! You'll get cookies...

EDIT(s): formatting.

31 Comments
Share

Save
92% Upvoted
This thread is archived
New comments cannot be posted and votes cannot be cast
SORT BY

BEST


level 1
[deleted]
9 points
·
3 years ago
That error probably has something to do with you not allocating enough memory, and therefore your probably overwriting some metadata the allocator requires.

    result = (char**) realloc(result, i);
    result[i - 1] = (char*) malloc(strlen(line));
How much memory do you think those two lines allocate, and is it enough for the data your writing into it?

Share
Report
Save


level 2
rafaelement
4 points
·
3 years ago
I think realloc takes a pointer to the first element of allocated memory and an int specifying the new size.

Could it be that it should be

result = (char**) realloc(result, i * sizeof(char*));
!?! Trying that out...

Share
Report
Save


level 3
rafaelement
6 points
·
3 years ago
thats it. BAM! Thank you!

Here you go: \uD83C\uDF6A!

Share
Report
Save


level 4
BitOBear
6 points
·
3 years ago
·
edited 3 years ago
Stupid old-man tricks from type safety and porting school?...

I used to make medical equipment software and mission critical autonomous systems.

Here's a sample of things I learned from that.

int i = 0; /* always count from zero and add since you index from zero. */

    /* always use sizeof(arrayvar[0]) instead of the underlying element type */
    /* and use the temporary, the optimizer will get rid of it and you aren't uploading this at 300 baud. */
    /* EDITED to fix one-off caught by /u/OldWolf2 */
    int newsize = (i+2)*sizeof(result[0]);  /* also a great debugger breakpoint if things seem to be kaka. 8-) */

    /* if realloc fails, you don't want to leak all this memory */ 
    char ** intermediate = (char **)realloc(result,newsize);
    if (!intermediate) break;
    result = intermediate;

    /* always sentinel an array of pointers with a null, you never know if the size and the result will get separated */
    result[i+1] = NULL;
    /* in fact you are only returning result so its _already_ separated */

    /* just handle the plus one here where you are making sure you aren't tempted to call strlen() twice */
    int line_length = strlen(line)+1;
    result[i] = malloc(line_length);
    /* check all the returns from any allocation routine */
    /* leaving a NULL in your vector will leak memory later */
    /* e.g. if malloc(80) fails, but a later malloc(20) would be fine you'll get a false sentinel and leak everything after the malloc(80) */
    if (!result[i]) break;

    /* NEVER strcpy(), and check out why we made line_length */
    strncpy(result[i],line,line_length); /* It bears repeating, NEVER strcpy() */
This sort of compulsive sanitation will save you a lot of time.

In particular the sizeof(result[0]) is super useful whenever you are allocating N instances of X as an array.

struct item {
    char a;
    char b;
    char c;
};
struct item * vector = NULL;
...
sizeof(struct item); /* three (3) on many platforms */
sizeof(vector[0]); /* possibly four (4), and maybe even eight (8), for memory alignment purposes */
EDIT: apparently the use of sizeof() has been fixed up a lot since I started. sizeof(arrayvar[0]) has always served we well as it's never done the wrong thing on any platform. But I don't know how long ago this whole thing was fixed up to be immaterial. Guess it happened while I was still being overly cautious. Even if the urgent need isn't still there, using the name of the variable with the zero'eth element's subscript will save you from ever having to go find all the sizeof(char-or-whatever) entries in the code if someone decided that you need to switch from char to wchar_t or int to long long or whatever. Old compilers are out there... waiting in the dark to trash your data... /scary-face

calloc() takes the item size and the item count separately and deals with the alignment issues internally -- according to the initial design.

realloc() doesn't -- indeed can not -- do any of that compensation -- if it's even necessary any more.

So if there's a pointer that is to be used as an array, ALWAYS use the size of the zeroeth element to find the size of the array elements for multiplying by the subsequent array length.

The resulting off-by-N problem and the usual heap corruption that follows are not fun to find and debug -- though that may be a tale from an eariler age according to some testing I just did 8-).

Plus, if you decide to change from char to wchar_t later, everything compensates by magic when you recompile.

Slightly longer, but much more robust:

for (int i = 0; fgets(line, sizeof(line), fp) != NULL; ++i) {
    /* EDITED to fix one-off caught by /u/OldWolf2 */
    int new_size = (i+2)*sizeof(result[0]);
    char ** intermediate = (char **)realloc(result,new_size);
    if (!intermediate)
        break;
    result = intermediate;
    result[i+1] = NULL;
    
    int line_length = strlen(line)+1;
    result[i] = malloc(line_length);
    if (!result[i])
        break;
    strncpy(result[i],line,line_length);
    
    printf("%p\n", result);
    printf("%s\n", line);
}
Share
Report
Save


level 5
rafaelement
2 points
·
3 years ago
/* always sentinel an array of pointers with a null, you never know if the size and the result will get separated / result[i+1] = NULL; / in fact you are only returning result so its already separated */

I am not sure I understand that. Is there a convention that pointer arrays are always followed by a NULL pointer, sort of the '\0' of char arrays? Makes sense...

strncpy() is always safer because it cannot iterate past the end of the write buffer. strcpy() can be used to smash stacks in racy code. Better to run off the end of an improperly terminated string during a read then during a write.

That was eye opening. Thanks.

Do you have a 'code sanity' blog or book or something!? I'd totally read that, you write well(words too).

Coming from medical devices, I understand why your code is so desinfected and bug-free.

Thanks for the help, old man :)

Share
Report
Save


level 6
BitOBear
2 points
·
3 years ago
I am not sure I understand that. Is there a convention that pointer arrays are always followed by a NULL pointer, sort of the '\0' of char arrays? Makes sense...

In C all the statically sized arrays -- e.g. int array[20]; -- you can find the size dynamically with sizeof nonsense as in sizeof(array)/sizeof(array[0]) == 20.

But once you pass an array in or out of a context like a function, you lose the [20]ish-ness.

int number_of_indexes(int array_arg[]) {
  /* it's _impossible_ to know the size of array_arg here */
}

int other_search_for_indexes(int * array_arg) {
  /* same problem here */
}
This is the core of the "string problem". You will notice the similarity of other_search_for_indexes(int *x) to some_string_function(char *str).

The core concept for resolving this is the "sentinel", a data value that doesn't belong in the valid data set but fits into the data type. For strings this is the special character with value zero -- a.k.a. '\\0'.

When you pass around other data types you need a similar sentinel, for an integer array you might use zero, but zero might be needed. So you usually have to do something annoying. You either need to pass the relevant array length along or you need to play games with signs or explicitly reserved values.

This sucks, but it's also why, for example, linux system calls all return non-negative numbers for success and negative-one for errors.

For a pointer however, there's a natural candidate. NULL which is really just (void *)0 -- that is the value zero cast to the pointer type.

So with the returning an array of pointers to strings, how will you tell how many lines were read from the file? Without manually adding the NULL you'd need to do something else.

One of the "best" techniques is to return a structure with an fractional array at the bottom.

struct ProperVector {
    size_t entries;
    /* other stuff you need */
    char *data[];
};

/* then do the allocations as (pseudocode) ... */

struct ProperVector * new_vect = realloc(X, sizeof(struct ProperVector) + X.entries*sizeof(char*));
And if you want to do super clever stuff you can use a sized array

struct ProperVector {
    size_t entries;
    /* other stuff you need */
    char *data[1];
};
That [1] leaves room for the sentinel and the rest of the overhead can go along with it too. (By that I mean it's easy and ready to pass the X.data vector into routines that want the NULL sentinel, even as you get to keep your overhead in line.)

Sometimes I use this same thing to keep strings in good order.

In high-performance applications I use pairs of pointers...

struct string {
    char * start;
    char * end;
};

struct buffer {
    struct string control;
    char buffer[1];
};
Or you can just go crazy...

struct buffer {
    struct string * fragments;
    char buffer[1];
};
The above is a way to keep a buffer and its subsections... so like if you are dividing up a string into a set of sub-strings, like when using regular expressions to carve a large buffer into potentially overlapping chunks.

The "string" structure is good for passing slices around. The buffer is also an extensible means of combining the slicing and the storage and it automatically remembers to allocate the extra character for the '\\0'.

I know I'm just tossing tidbits out there and asking you to imagine the uses. But as you think it through, using pointer pairs lets you do some very high-performance zero-copy stuff.

Once you really think about the very simple idea that "sentinels are useful" but also "sentinels suck" a number of patterns start leaping out.

P.S. It's late and I'm a little punchy, so I'll check this ramble tomorrow to make sure its not pure insanity. 8-)

Share
Report
Save


level 7
rafaelement
1 point
·
3 years ago
having that struct properVector makes a ton of sense to me, having started out with java.

struct ProperVector {
    size_t entries;
    /* other stuff you need */
    char *data[1];
};
The [1] is like having a placeholder that is always NULL and gets 'pushed' behind newly realloc'd elements? Thats great, given all functions working on it obey the rules.

'In situ' algorithms get a whole new meaning with your struct string. I am going to try implementing merge sort for strings using the crazy struct, that seems like a good match since if I do the algorithm correctly, there should be no overlaps.

Thanks for taking the time to teach a greenhorn!

Share
Report
Save


level 8
BitOBear
1 point
·
3 years ago
·
edited 3 years ago
You have to "push" the NULL yourself. That is' it's still your job to mark the end of the array with X.data[X.entries] = NULL before passing X.data into an array that expects a sentinel-protected input.

The place holder is not guaranteed to be always null since the result of realloc() and malloc() is a length of memory with no grantee that that length was filled with zeros. It just gets rid of the pesky need to remember the plus-one. The technique just guarantees that you won't mess up the size math in the bad direction.

So if you are calling a function that takes an argument such as char *array[] like execlv and friends you might build the argv[] argument array dynamically as we are discussing then "fix it up" right before use. (example skips aggressive argument and error checking for to focus on the technique).

void PrepareVector(struct ProperVector & X) {
    X->data[X->entries] = NULL;
}
...
struct ProperVector * argumets = VectorFactory();
memset(arguments,0);
...
SafeAppend(&arguments,some_string);
SafeAppend(&arguments,other_string);
PrepareVector(&arguments);
execv("/some/command",arguments->data);
... /* hopefully we dont get here because of the exec */
Note that this technique is part of why, in C++, you call c_str() on a std::string when you pass it into a typical C Library or System call. The string implementation has been leaving room for the eventual ASCII NUL character in all of its allocations and whanot, but c_str() needs to decorate the buffer with the actual NUL before it's ready for use in system calls and such.

I just find the non-zero array at the end helpful instead of forcing myself to remember the +1 all the time.

IMPLEMENTATION NOTE: Using the char data[1] technique can trigger unwanted bounds checking on some systems because you are clearly extending that array but it has an explicit length in the mind of the compiler. For GCC, for example, you may want to decorate the entry with a dont-bounds-check-me attribute or collect up your vector implementation into a compilation unit that you specially mark with non-bounds-check options to silence warnings/error you don't get with plain char data[];. I did the proper vector thing for a while in the olden times, but then switched to the two-pointer methodology later but before C bounds checking was common. YMMV.

If the platform makes implementation difficult, it's still useful to have this sort of technique in your brain and well understood, so that you can pair the ideal to the actual of whatever you are doing.

Share
Report
Save


level 9
rafaelement
1 point
·
3 years ago
GCC doesn't like that! So I'm gonna go with the struct of char pointer pairs option.

Thanks once more for your thoughts!

Share
Report
Save


level 10
BitOBear
2 points
·
3 years ago
·
edited 3 years ago
Cool.

So remember:

X.end - x.start is strlen() only faster.

you still want to plus-one your allocations so that you can *x.end = '\0'; before passing a string to a library or system call.

people will give you the stink-eye for doing this until they catch on. 8-)

Best to make a few factory and manipulations functions for the points above.

Now lets pretend you are writing a simple editor...

You probably want easily mutable string buffers. (the following is typed in from the top of my head, so may contain errors. I am no typing all the error constraints you should check. Code for example purposes only.)

struct MutableStringBuffer {
    char *start;
    char *gap;
    char *gap_extent;
    char * end;
};

MutableStringBuffer *
allocate_buffer(size_t bufferSize) {
    MutableStringBuffer retval = malloc(sizeof(MutableStringBuffer));
    if (retval) {
        /* going to nul terminate the buffer in the name of paranoia */
        /* in this example. */
        retval->start = retval->gap = malloc(bufferSize+1);
        retval->end = retval->gap_extent = retval->start+bfferSize+1;
        /* prevent the worst case erroneous read by a systcall etc */
        *(retval->end) = '\0';
    }
return retval;

void
SetInsertPoint(MutableStringBuffer * buffer, offset_t offset) {
    char * mark = buffer->start + offset;
    /* doing math and calling memmove() is better, but this is instructive and good enough... */
    while (buffer.gap > mark &&
           buffer.gap > buffer.start) {
        --buffer->gap;
        --buffer->gap_extent;
        *buffer->gap_extent = *buffer->gap;
    }
    while (buffer->gap < mark &&
           buffer->gap_extent < buffer->end) {
        *buffer->gap = *buffer->gap_extent;
        ++buffer->gap;
        ++buffer->gap_extent;
    }
}

void
SetInsertPointHead(MutableStringBuffer * buffer) {
    SetInsertPoint(buffer,0);
}

void
SetInsertPointTail(MutableStringBuffer * buffer) {
    SetInsertPoint(buffer, (buffer->end - buffer->start));
}

offset_t
GetBufferSize(MutableStringBuffer * buffer) {
    return buffer->end - buffer->start;
}

offset_t
GetUnusedSize(MutableStringBuffer * buffer) {
    return buffer->gap_extent - buffer->gap;
}

offset_t
GetStringSize(MutableStringBuffer * buffer) {
    return GetBufferSize(buffer) - GetUnusedSize(buffer);
}

/* you need some error checking here for sure, I'm only doing some */
void
ResizeBuffer(MutableStringBuffer * buffer, size_t newsize) {
    SetInsertPointTail(buffer);
    size_t valid_string_size = buffer->gap - buffer->start;
    /* include make room for null*/
    char * newbuffer = realloc(buffer->start, newsize+1);
    if (newbuffer) {
        buffer->start = newbuffer;
        buffer->end = buffer->gap_extent = buffer->start + newsize; 
        buffer->gap = buffer->start + valid_string_size;
        /* at this moment we might be _invalid_ if the resize shrunk the buffer enough to truncate the string, so fix that... */
        if (buffer->gap > buffer->gap_extent) {
            buffer->gap = buffer->gap_extent;
        }
        *buffer->end = '\0'; /* safety nul */
    }
}
So dropping to pseudo code

If you want to insert a character you move the insert point with the function above, then do a *buffer->gap++ = newchar; type operation.

If yoou want to insert a whole string you make sure the buffer is big enough by subtracting the used size from the buffer size, then you move the insert point then you copy the string in at gap and move gap by that new length. You are repeating insert character operation strlen() times but all at once.

Finally to delete. Move the insert point to the start of the characters you want to delete, then advance the gap_extent by the number of characters you are deleting. (you don't have to overwrite the data, it's now just noise in the gap.

Finally, to pass a buffer to a syscall or whatever, move the gap to the end as above, then cram a nul into the address pointed to by gap SetInsertPointTail(buffer); *buffer->gap = '\\0'; before passing buffer->start to the library call.

The entire idea of using two pointers for strings, and four for editable buffers is that, in the classic mathematical sense -- and in the C++ iterator sense -- you can always be safe and sure in the knowledge that a range such as [start,end) is valid and of a size that can be determined by simple subtraction. So any sets of pairs of related pointers known valid across a contiguous memory range are fully move safe. So the buffer [start,end) can have the gap [start,end) slid around within it, as long as you juggle the characters across the gap as the gap slides. etc.

Your only important duty is that any substring pairs of pointer never ever outlive the buffer into which they point.

To that end, the absolute start of the storage master string/buffer must never move (outside of realloc() of course) so that you never lose the reference for deallocation. If you are tempted to move buffer->start you are doing it wrong. 8-)

The above rules don't hold for substrings.

Don't mix substrings and editable buffers. (This is why all java strings are immutable, that's one way to ensure you never lose the point of allocation.)

Now go play until this all makes lots of sense.

Once this is really how you think about all strings, going back to the intrinsic calls like strncpy() will be easier.

This sort of pointer manipulation and bounding is kind of like learning calculus and then never needing to use it again. Knowing it changes your mind in helpful ways.

Share
Report
Save
Continue this thread
 


level 5
OldWolf2
1 point
·
3 years ago
·
edited 3 years ago
Your code accesses out of bounds:

int newsize = (i+1)*sizeof(result[0]);
...

result[i+1] = NULL;
Array dimension of i + 1 means valid indices are 0 through i.

I disagree with the strategy of using both length-counting and null-termination. It introduces an extra point of failure and makes the code more complicated to maintain both things. You now have to do 2 things right, instead of having to do 1 thing right.

Also,strncpy would be better off written as strcpy. You already checked the length, and strncpy is a dangerous function in general. Changing your "NEVER strcpy" policy to "NEVER strncpy" would lead to an improvement in code safety.

Share
Report
Save


level 6
BitOBear
2 points
·
3 years ago
·
edited 3 years ago
The one-off error is correct of you to catch, the first instance should be (i+2)*sizeof(result[0])... nobody's perfect. 8-)

Since the function only returns result the NULL sentinel is mandatory. There is no other constraint.

strncpy() is always safer because it cannot iterate past the end of the write buffer. strcpy() can be used to smash stacks in racy code. Better to run off the end of an improperly terminated string during a read then during a write.

So having done the work to ensure the nul ('\0') by fixing the length, strncpy() is better.

both strcpy() and strncpy() are horribly flawed, but like I said, I'd rather protect the system from errant writing than reading.

The "real" "best" call is strncat() after prepping dest with *dest='\\0'; before the call but I didn't want to go that far with what was already a long post. An entire second half-post on not screwing up strings was a little too much. 8-)

Share
Report
Save


level 7
rafaelement
1 point
·
3 years ago
reddit trick is putting the text in the box between two grave accents, ascii 0x60.

Share
Report
Save


level 7
OldWolf2
1 point
·
3 years ago
strcpy cannot write past the end of the buffer, when you just allocated the buffer by using strlen of the thing you are copying from, + 1.

Both functions have their issues, but it is easier to use strcpy correctly: do a length check first. If you want to use a function that does not require any pre-checks or post-actions then do not use either of those options.

So having done the work to ensure the nul ('\0') by fixing the length, strncpy() is better

Why is it better? strcpy would be more slightly more efficient in this case (if the compiler does not optimize), although that is immaterial next to the security aspect we were discussing.

Better to run off the end of an improperly terminated string during a read then during a write.

Not really. Bad reads lead to awful bugs too, especially ones that seem to work OK in testing and then fail in the field.

Share
Report
Save


level 8
BitOBear
1 point
·
3 years ago
·
edited 3 years ago
Opinions... /sigh.

strcpy() CAN be coerced to miswrite the destination buffer. Not in this program if we presume that it is single threaded, and not in this program because there is no sign aliases to the pointers. In "best practices", however, you always protect the write with a bounds-check. Period.

Most of this program wold be better dealt with via strdup() anyway, but if yous still don't get why I prefer strncpy() to strcpy():

long read is a safer bad outcome than long write.

there is no negative efficiency to strncpy() since

we had to do the strlen() to size the buffer anyway

we exact-sized the buffer to a copy length so the same number of bytes that an unperturbed strcpy() would copy absent input corruption.

with asynchronous input corruption on the table (via string arguments or threading, which probably isn't the case here, admittedly) the distinction is real

Best Practice is that thing you "always do" so that when it does matter you didn't make the "bad" choice by habit.

Explicitly bounded writes are always the "Best Practice" function call choice since stack and heap integrity are always on the line and a runaway read will not damage a stack or a heap.

Share
Report
Save


level 9
OldWolf2
1 point
·
3 years ago
Best Practice is that thing you "always do" so that when it does matter you didn't make the "bad" choice by habit.

Not using strncpy at all is a pretty good practice imo.

a runaway read will not damage a stack or a heap.

Undefined behaviour can cause anything . It could read bogus data leading your program to misbehave and then go on to write rubbish elsewhere, for example.

Share
Report
Save


level 9
OldWolf2
1 point
·
3 years ago
Best Practice is that thing you "always do" so that when it does matter you didn't make the "bad" choice by habit.

Not using strncpy at all is a pretty good practice imo.

a runaway read will not damage a stack or a heap.

Undefined behaviour can cause anything . It could read bogus data leading your program to misbehave and then go on to write rubbish elsewhere, for example.

Share
Report
Save


level 10
BitOBear
1 point
·
3 years ago
·
edited 3 years ago
Length of string read nets undefined behavior rarely, if at all, unless it is in concert with the design and implementation that sloppily uses string buffers without protections.

Describe for us, if you would, an undefined behavior caused by a string read that doesn't hinge upon a later failure to use a constrained write (such as using sprintf() instead of snrintf()) and/or check the return value of such a function to discover that it ran out of destination buffer.

That is, crash, if you will, a program using an unconstrained read without, say, shaving off return value precision into a presumed data type -- e.g. you can crash/hang a program using things like.

/* pretending to "know" that a string has a limited possible size sch as */
uint8_t length = strlen(unsanitized_string);
/* or */
char buffer[1000];
sprintf(buffer,"%s", unsanitized_string);
/* or */
snprintf(buffer,sizeof(buffer),"%s :: %s",unsanitized_string,other_string);
/* ^^^ Didn't make sure return value was less-than sizeof(buffer) */
FunctionBadForAssumingStringSanityOf(buffer);
/* ^^^ function that crashes program if it can't find two strings and the " :: " glyph */
So yes, if you make a mess of all your string handling then feel free to use strcpy() as you might as well hope for the segfault or bus error on the immediate write.

Shall we argue vi versus emacs next? 8-)

Share
Report
Save


level 4
[deleted]
3 points
·
3 years ago
No problem :)
I guess you fixed the other bug as well then? HINT: "zero terminated strings"

Share
Report
Save


level 5
rafaelement
1 point
·
3 years ago
Haha, I actually took that bit of code out. Should I allocate space for one more char and set that to '\0' ?

    result[i - 1] = (char*)malloc(strlen(line) + 1);
    strcpy(result[i - 1], line);
    result[i - 1][strlen(line)+1] = '\0';
Thanks for your help.

Share
Report
Save


level 6
jedwardsol
2 points
·
3 years ago
strcpy copies the nul, so the last line isn't necessary.

But, yes, strlen(line)+1 is correct.

Share
Report
Save


level 6
FeelTheEmailMistake
2 points
·
3 years ago
As jedwardsol said, this line isn't necessary, because strcpy() automatically adds the NUL:

result[i - 1][strlen(line)+1] = '\0';

However, if you did have something like that, note that you'd want to use [strlen(line)], not [strlen(line)+1], because of 0-based indexing.

Share
Report
Save


level 7
rafaelement
1 point
·
3 years ago
thats right... there is this xkcd about segfaults that I'm sure you know. It applies here.

Share
Report
Save


level 8
FeelTheEmailMistake
2 points
·
3 years ago
Could be worse than a segfault, depending on how the allocator manages its internal bookkeeping information on the heap. ;)

Even on the stack, a one-byte NUL overflow may be exploitable, though with today's OS and compiler defense mechanisms, it's not as likely. On the x86, for instance, if the array was positioned alongside the saved frame pointer (which compilers would typically do if the array was the first thing declared in a block), a one-byte NUL overwrite of the saved frame pointer's least significant byte would affect a critical reference point in the parent function's stack frame. That parent function could then start reading pointers from attacker-controlled words or grab its saved return address from an attacker-controlled word upon ret.

Even the most innocuous-seeming problems can be dangerous.

Share
Report
Save


level 3
balkenbrij
2 points
·
3 years ago
also, it's better to use another variable for the return value otherwise you can't free when it fails and returns null. If you need to read a lot variable length data it might also be neat to wrap it into a structure with a counter and initial allocated block size. You then only resize when counter == the allocated block size by double that ammount. e.g. start with a block for 16 entries (best guess of input) and count the items which you add upto 16 entries, then resize to 32 counting upto that, then resize to 64 etc. etc. This is how the c++ vector works for instance.

Share
Report
Save


level 4
rafaelement
1 point
·
3 years ago
thats neat. Too much in this situation, but i will keep it in mind.

Variable: thanks, done it!

Share
Report
Save


level 1
Drainedsoul
2 points
·
3 years ago
result = (char**) realloc(result, i);

This line is broken. If realloc fails (and returns NULL) it won't free the pointers passed to it, but you replace the old pointer with NULL, so it's a leak.

You also don't check the return value of realloc and just assume it succeeds, which is also horribly broken.

May not be the specific problem you're running into, but it's still broken and should be fixed.

Share
Report
Save


level 2
rafaelement
2 points
·
3 years ago
I see! fixed it, thank you.

Share
Report
Save


level 1
pinealservo
2 points
·
3 years ago
After reading all the comments here, I think the takeaway lesson is that the C standard library is your enemy, and you had better study the hell out of its weaknesses and plan every engagement with it as a potentially fatal one. :)

Share
Report
Save


level 2
rafaelement
1 point
·
3 years ago
its a boss battle :) yep, now I know why everyone told me to rtfm.

Share
Report
Save
COMMUNITY DETAILS
r/C_Programming
45.6k

Subscribers
131

Online
The subreddit for the C programming language

SUBSCRIBE
CREATE POST
R/C_PROGRAMMING RULES
1.
Format your code
2.
Only C is on topic
MODERATORS
u/gthank
u/FUZxxl
u/theboxingfox
u/nderflow
VIEW ALL MODERATORS
About
Careers
Press
Advertise
Blog
Help
The Reddit App
Reddit Coins
Reddit Premium
Reddit Gifts
Content Policy| Privacy Policy
User Agreement| Mod Policy
© 2019 Reddit, Inc. All rights reserved
BACK TO TOP
