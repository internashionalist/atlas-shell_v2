cat -n _which.c >> _which.copy > _which.copy2 && ls -al .. > ls1 >> ls2 && ls >> _ls.out ; ls > _ls2.out & pwd > _pwd.out
# cat -n _which.c > _which.copy # && ls -l -a .. > _ls.out| echo hello world! > hw.out # || semi << LL ; end > R < L >> RR
# twoAmp >> RR > R && bar | semi ; twoBar || amp  > R & end < L
# pwd < L >> RR ;  git status -s  --show-stash || echo hello again! # | sed A B C >> RR  << LL  |  end > R << LL
# grep include *.h >> RR < L;
