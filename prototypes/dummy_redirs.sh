cat -n _which.c >> ./output/which1.out > ./output/which2.out > ./output/which3.out && ls -al .. > ./output/ls1.out >> ./output/ls2.out && ls >> ./output/ls3.out ; ls > ./output/ls4.out & pwd > ./output/pwd1.out
# cat -n _which.c > _which.copy # && ls -l -a .. > _ls.out| echo hello world! > hw.out # || semi << LL ; end > R < L >> RR
# twoAmp >> RR > R && bar | semi ; twoBar || amp  > R & end < L
# pwd < L >> RR ;  git status -s  --show-stash || echo hello again! # | sed A B C >> RR  << LL  |  end > R << LL
# grep include *.h >> RR < L;
