> 리액트 프로젝트에서 반복적인 내용을 효율적으로 보여 주고 관리하는 방법을 알아 보자.

# 6.1 자바스크립트 배열의 map() 함수

# 6.2 데이터 배열을 컴포넌트 배열로 변환하기

# 6.3 key

컴포넌트 props를 설정하듯이 설정하면 됨

고유한 값이 없을 때만 index 값을 key로 사용하기.

BUT 권장하지 않음. ⇒ index를 key로 사용하면 배열이 변경될 때 효율적으로 리렌더하지 못함.

-   참고

    [Warning: Each child in an array or iterator should have a unique “key” prop.](https://www.notion.so/Warning-Each-child-in-an-array-or-iterator-should-have-a-unique-key-prop-60245a51465041a9b961cffc9102019a)

# 6.4 응용

## 초기 상태 설정하기

객체로 배열을 구성하게 하기. {id: 1, text: "눈사람"} 이렇게 구성해야 고유 id 값을 key로 쓸 수 있음(map에)

## 데이터 추가 기능 구현하기

concat 이용

++ 배열 형태의 state 건드릴 때는 concat으로 새로운 배열 만들어서 state에 저장해주기. 기존의 state에 해당하는 배열을 건드리지 않는 게 좋음.

-   참고

    [Why Immutability is important](https://www.notion.so/Why-Immutability-is-important-542e3dca878b409dab0af5a9ec09ff6b)

## 데이터 제거 기능 구현하기

filter 함수 이용

-   예제 코드

    ```jsx
    import React, { useState } from "react";

    const IterationSample = () => {
        const [names, setNames] = useState([
            { id: 1, name: "아르미" },
            { id: 2, name: "동구" },
            { id: 3, name: "진" },
        ]);
        const [inputText, setInputText] = useState("");
        const [nextId, setNextId] = useState(4);

        const onChange = (e) => {
            setInputText(e.target.value);
        };
        const onClick = () => {
            const newNames = names.concat({ id: nextId, name: inputText });
            setNames(newNames);
            setNextId(nextId + 1);
            setInputText("");
        };
        const onRemove = (id) => {
            const newNames = names.filter((n) => n.id !== id);
            setNames(newNames);
        };
        const onKeyPress = (e) => {
            if (e.key === "Enter") {
                onClick();
            }
        };
        const nameList = names.map(({ id, name }) => {
            return (
                <li
                    key={id}
                    onDoubleClick={() => {
                        onRemove(id);
                    }}
                >
                    {name}
                </li>
            );
        });

        return (
            <div>
                <h1>iteration sample</h1>
                <ul>{nameList}</ul>
                <input
                    onChange={onChange}
                    value={inputText}
                    placeholder={"이름을 적으세요"}
                    onKeyPress={onKeyPress}
                ></input>
                <button onClick={onClick}>추가</button>
            </div>
        );
    };

    export default IterationSample;
    ```

# 6.5 정리

key는 고유해야 한다.
