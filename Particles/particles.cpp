#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define mul 10000
#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

//________________________________________________________________________//

/*** Particle Class ***/

/*
 *  The particles class. It contains the velocity and the start time
 *  of each particle that will be fired from the cannons.
 */
class Particle {

private:

    int velocity, start, destroyed;

public:

    void put(int velocity, int start);
    long double distance(long long int t);
    long long int end(int len);
    bool isDestroyed();
    bool skip(int t);
    void destroy();

};

/*
 *  Puts velocity and start time read.
 *  @param velocity The velocity.
 *  @param startTime The start time.
 */
void Particle::put(int velocity, int start)  {

    this->velocity = velocity;
    this->start = start;
    this->destroyed = 0;

}

/*
 *  Calculates the distance travelled so far in time t.
 *  @param t The current time stamp.
 *  @return distance travelled.
 */
long double Particle::distance(long long int t) {

    double realTime;

    realTime = 1.0 * t / mul;

    return (velocity * (realTime - start));

}

/*
 *  Calculates when the particle will reach the other end.
 *  @param len The length to travel.
 *  @return time to travel to other end.
 */
long long int Particle::end(int len) {

    long double result;

    result = 1.0 * len / velocity;
    result *= mul;
    result = ceil(result);
    result += start * mul;

    return (long long int)result;

}

/*
 * Find if object is destroyed.
 * @return true iff destroyed is 1.
 */
bool Particle::isDestroyed() {

    return (destroyed == 1);

}

bool Particle::skip(int t) {

    return (t < (start * mul));

}

void Particle::destroy() {

    this->destroyed = 1;

}

//________________________________________________________________________//

/*
 *  The EndPair Class. Contains for each particle (with index)
 *  the time it needs to reach the other end.
 */
class EndPair {

public:

    int index;
    long long endTime;

    void put(int index, long long int endTime);

    bool operator < (const EndPair &other) const {

        return (endTime < other.endTime);

    }

};

void EndPair::put(int index, long long int endTime) {

    this->index = index;
    this->endTime = endTime;

}

//________________________________________________________________________//

/*** Pair Class ***/

/*
 *  A simple integer pair class.
 */
class Pair {

public:

    int left, right;

};

//________________________________________________________________________//

/*** Functions Declaration ***/

int read_int();
long long int min(vector<EndPair> &le, vector<Particle> &lp, int &li, vector<EndPair> &re, vector<Particle> &rp, int &ri);

Pair find_collision(int size, int len, long long int &timeLeft, long long int &timeRight, vector<Particle> &left, vector<Particle> &right);

void read_particles(int cannons, vector<Particle> &particles);
void find_ends(int cannons, int length, vector<Particle> &particles, vector<EndPair> &ends);

//________________________________________________________________________//

/*** Main ***/

int main() {

    int cannons, length, collisions;
    int i;
    int li, ri;
    long long int timeLeft, timeRight;

    cannons = read_int();
    length = read_int();
    collisions = read_int();

    vector<Particle> left(cannons);
    vector<EndPair> endLeft(cannons);
    vector<Particle> right(cannons);
    vector<EndPair> endRight(cannons);

    read_particles(cannons, left);
    read_particles(cannons, right);

    find_ends(cannons, length, left, endLeft);
    find_ends(cannons, length, right, endRight);

    sort(endLeft.begin(), endLeft.end());
    sort(endRight.begin(), endRight.end());


    //for (i = 0; i < cannons; i++)
    //    cout << "endLeft[" << endLeft[i].index << "] = " << 1.0 * endLeft[i].endTime / mul << endl;

    //for (i = 0; i < cannons; i++)
    //    cout << "endRight[" << endRight[i].index << "] = " << 1.0 * endRight[i].endTime / mul << endl;


    vector<Pair> collision(collisions);

    timeLeft = 0;
    li = 0;
    ri = 0;
    for (i = 0; i < collisions; i++) {

        timeRight = min(endLeft, left, li, endRight, right, ri);
        //cout << timeRight << endl;
        //cout << li << " " << ri << endl;
        collision[i] = find_collision(cannons, length, timeLeft, timeRight, left, right);

    }

    for (i = 0; i < collisions; i++)
        cout << (collision[i].left + 1) << " " << (collision[i].right + 1) << endl;

    return 0;

}

//________________________________________________________________________//

/*** Functions Code ***/

int read_int() {

    int d = 0, x = 0;
    char c;

    while (1)  {

        if (bpos >= bsize) {

            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);

        }

        c = buffer[bpos++];
        if (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
            return x;

    }

    return -1;

}

/*
 *  Find minimum of two integers.
 *  @param a First integer.
 *  @param b Second integer.
 *  @return the minimum.
 */
long long int min(vector<EndPair> &le, vector<Particle> &lp, int &li, vector<EndPair> &re, vector<Particle> &rp, int &ri) {

    while (lp[le[li].index].isDestroyed())
        li++;

    while (rp[re[ri].index].isDestroyed())
        ri++;

    if (le[li] < re[ri])
        return le[li++].endTime;

    return re[ri++].endTime;

}

/*
 *  A function to read the velocities and start times of
 *  the particles for each cannon.
 *  @param cannons The number of particles to be shot.
 *  @param particles The vector containing the cannons particle specs.
 */
void read_particles(int cannons, vector<Particle> &particles) {

    int i, t, v;

    for (i = 0; i < cannons; i++) {

        t = read_int();
        v = read_int();
        particles[i].put(v, t);

    }

}

/*
 *  A function to find, for each particle, the time to reach the other end.
 *  @param cannons The number of particles to be shot.
 *  @param length The distance to be travelled.
 *  @param particles The particles with velocities and start times.
 *  @param ends The int vector with endTimes;
 */
void find_ends(int cannons, int length, vector<Particle> &particles, vector<EndPair> &ends) {

    int i;

    for (i = 0; i < cannons; i++)
        ends[i].put(i, particles[i].end(length));

}

Pair find_collision(int size, int len, long long int &timeLeft, long long int &timeRight, vector<Particle> &left, vector<Particle> &right) {

    int i;
    long long int mid;
    int count;
    long double max, temp;
    Pair result;

    while (timeLeft != (timeRight - 1)) {

        max = 0;
        count = 0;
        mid = (timeLeft + timeRight) / 2;

        cout << "mid = " << mid << endl;

        for (i = 0; i < size; i++) {

            if (left[i].isDestroyed())
                continue;

            if (left[i].skip(mid))
                break;

            temp = left[i].distance(mid);
            cout << "leftDis[" << i << "] = " << temp << endl;

            if (temp > max)
                max = temp;

        }

        for (i = 0; i < size; i++) {

            if (right[i].isDestroyed())
                continue;

            if (right[i].skip(mid))
                break;

            temp = right[i].distance(mid);
            cout << "rightDis[" << i << "] = " << temp << endl;

            if (max + temp >= len) {

                count++;
                break;

            }

        }

        if (count == 0) {

            cout << "No collision yet" << endl;
            timeLeft = mid;

        } else {

            cout << "Collisions found" << endl;
            timeRight = mid;

        }

    }

    cout << "Final timeLeft = " << timeLeft << endl;
    cout << "Final timeRight = " << timeRight << endl;

    max = 0;

    for (i = 0; i < size; i++) {

        if (left[i].isDestroyed())
            continue;

        if (left[i].skip(timeRight))
            break;

        temp = left[i].distance(timeRight);
        //cout << "leftDis[" << i << "] = " << temp << endl;

        if (temp > max) {

            max = temp;
            result.left = i;

        }

    }

    for (i = 0; i < size; i++) {

        if (right[i].isDestroyed())
            continue;

        if (right[i].skip(timeRight))
            break;

        temp = right[i].distance(timeRight);
        //cout << "rightDis[" << i << "] = " << temp << endl;

        if (max + temp >= len) {

            result.right = i;
            break;

        }

    }

    timeLeft = timeRight;
    left[result.left].destroy();
    right[result.right].destroy();

    return result;

}
