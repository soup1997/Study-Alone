function [xm, ym] = GetBallPos(index)

persistent imgBg
persistent firstRun

if isempty(firstRun)
    imgBg = imread('./Img/bg.jpg');  
    firstRun = 1;
end

xm = 0;
ym = 0;

imgWork = imread(['./Img/', int2str(index), '.jpg']);
imshow(imgWork);

fore = imabsdiff(imgWork, imgBg);
fore = (fore(:, :, 1) > 10 | fore(:, :, 2) > 10 | (fore(:, :, 3)> 10));

L = logical(fore); % 숫자형 값을 논리값(Logical)으로 변환
stats = regionprops(L, 'area', 'centroid');
area_vector = [stats.Area];
[~, idx] = max(area_vector);

centroid = stats(idx(1)).Centroid;

% 공의 중심 좌표 반환
xm = centroid(1) + 15*randn(1);
ym = centroid(2) + 15*randn(1);